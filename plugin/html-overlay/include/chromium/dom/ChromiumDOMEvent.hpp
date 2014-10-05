/*
Copyright (c) 2013 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#if defined(CHROMIUM)
#pragma once

#include "minko/Common.hpp"
#include "minko/dom/AbstractDOMMouseEvent.hpp"
#include "minko/dom/AbstractDOMElement.hpp"
#include "include/cef_render_process_handler.h"

namespace chromium
{
    namespace dom
    {
        class ChromiumDOMEvent : public virtual minko::dom::AbstractDOMEvent
        {
        public:
            typedef std::shared_ptr<ChromiumDOMEvent> Ptr;
            ~ChromiumDOMEvent();

        protected:
            ChromiumDOMEvent(CefRefPtr<CefV8Value>, CefRefPtr<CefV8Context>);

        public:
            static inline
            Ptr
            create(CefRefPtr<CefV8Value> value, CefRefPtr<CefV8Context> context)
            {
                return std::shared_ptr<ChromiumDOMEvent>(new ChromiumDOMEvent(value, context));
            }

            void
            preventDefault();

            void
            stopPropagation();

            std::string
            accessor();

            std::string
            type();

            minko::dom::AbstractDOMElement::Ptr
            target();

			static
			void
			clearAll();

			void
			clear();
            
        protected:

            CefRefPtr<CefV8Value>
            getFunction(std::string name);

            CefRefPtr<CefV8Value>
            getProperty(std::string name);

            std::atomic<bool> _blocker;

            static
            std::list<Ptr> _events;

            CefRefPtr<CefV8Context> _v8Context;

            bool _cleared;

            CefRefPtr<CefV8Value> _v8NodeObject;
        };
    }
}
#endif