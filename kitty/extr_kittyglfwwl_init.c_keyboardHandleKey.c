#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct wl_keyboard {int dummy; } ;
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_4__ {int /*<<< orphan*/  keyRepeatTimer; int /*<<< orphan*/ * keyboardFocus; scalar_t__ key; } ;
struct TYPE_5__ {scalar_t__ keyboardRepeatRate; TYPE_1__ keyRepeatInfo; int /*<<< orphan*/  eventLoopData; scalar_t__ keyboardRepeatDelay; int /*<<< orphan*/  xkb; int /*<<< orphan*/ * keyboardFocus; } ;
struct TYPE_6__ {TYPE_2__ wl; } ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 scalar_t__ GLFW_FALSE ; 
 int GLFW_PRESS ; 
 int GLFW_RELEASE ; 
 scalar_t__ GLFW_TRUE ; 
 scalar_t__ WL_KEYBOARD_KEY_STATE_PRESSED ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  changeTimerInterval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  glfw_xkb_handle_key_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ glfw_xkb_should_repeat (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  toggleTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void keyboardHandleKey(void* data,
                              struct wl_keyboard* keyboard,
                              uint32_t serial,
                              uint32_t time,
                              uint32_t key,
                              uint32_t state)
{
    _GLFWwindow* window = _glfw.wl.keyboardFocus;
    if (!window)
        return;
    int action = state == WL_KEYBOARD_KEY_STATE_PRESSED ? GLFW_PRESS : GLFW_RELEASE;
    glfw_xkb_handle_key_event(window, &_glfw.wl.xkb, key, action);
    GLFWbool repeatable = GLFW_FALSE;

    if (action == GLFW_PRESS && _glfw.wl.keyboardRepeatRate > 0 && glfw_xkb_should_repeat(&_glfw.wl.xkb, key))
    {
        _glfw.wl.keyRepeatInfo.key = key;
        repeatable = GLFW_TRUE;
        _glfw.wl.keyRepeatInfo.keyboardFocus = window;
    }
    if (repeatable) {
        changeTimerInterval(&_glfw.wl.eventLoopData, _glfw.wl.keyRepeatInfo.keyRepeatTimer, (double)(_glfw.wl.keyboardRepeatDelay) / 1000.0);
    }
    toggleTimer(&_glfw.wl.eventLoopData, _glfw.wl.keyRepeatInfo.keyRepeatTimer, repeatable ? 1 : 0);
}