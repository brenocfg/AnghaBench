#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct wl_keyboard {int dummy; } ;
struct TYPE_8__ {int tv_sec; int tv_nsec; } ;
struct TYPE_7__ {int tv_nsec; int tv_sec; } ;
struct itimerspec {TYPE_3__ it_value; TYPE_2__ it_interval; } ;
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_6__ {int /*<<< orphan*/  modifiers; } ;
struct TYPE_9__ {int keyboardRepeatRate; int keyboardLastKey; int keyboardRepeatDelay; int /*<<< orphan*/  timerfd; scalar_t__ keyboardLastScancode; TYPE_1__ xkb; scalar_t__ serial; int /*<<< orphan*/ * keyboardFocus; } ;
struct TYPE_10__ {TYPE_4__ wl; } ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 int GLFW_PRESS ; 
 int GLFW_RELEASE ; 
 scalar_t__ WL_KEYBOARD_KEY_STATE_PRESSED ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwInputKey (int /*<<< orphan*/ *,int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ inputChar (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  timerfd_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct itimerspec*,int /*<<< orphan*/ *) ; 
 int toGLFWKeyCode (scalar_t__) ; 

__attribute__((used)) static void keyboardHandleKey(void* data,
                              struct wl_keyboard* keyboard,
                              uint32_t serial,
                              uint32_t time,
                              uint32_t key,
                              uint32_t state)
{
    int keyCode;
    int action;
    _GLFWwindow* window = _glfw.wl.keyboardFocus;
    GLFWbool shouldRepeat;
    struct itimerspec timer = {};

    if (!window)
        return;

    keyCode = toGLFWKeyCode(key);
    action = state == WL_KEYBOARD_KEY_STATE_PRESSED
            ? GLFW_PRESS : GLFW_RELEASE;

    _glfw.wl.serial = serial;
    _glfwInputKey(window, keyCode, key, action,
                  _glfw.wl.xkb.modifiers);

    if (action == GLFW_PRESS)
    {
        shouldRepeat = inputChar(window, key);

        if (shouldRepeat && _glfw.wl.keyboardRepeatRate > 0)
        {
            _glfw.wl.keyboardLastKey = keyCode;
            _glfw.wl.keyboardLastScancode = key;
            if (_glfw.wl.keyboardRepeatRate > 1)
                timer.it_interval.tv_nsec = 1000000000 / _glfw.wl.keyboardRepeatRate;
            else
                timer.it_interval.tv_sec = 1;
            timer.it_value.tv_sec = _glfw.wl.keyboardRepeatDelay / 1000;
            timer.it_value.tv_nsec = (_glfw.wl.keyboardRepeatDelay % 1000) * 1000000;
        }
    }
    timerfd_settime(_glfw.wl.timerfd, 0, &timer, NULL);
}