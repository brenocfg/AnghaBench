#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct input_event {scalar_t__ type; scalar_t__ code; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  e ;
struct TYPE_11__ {int /*<<< orphan*/  fd; } ;
struct TYPE_12__ {int present; TYPE_2__ linjs; } ;
typedef  TYPE_3__ _GLFWjoystick ;
struct TYPE_10__ {scalar_t__ dropped; } ;
struct TYPE_13__ {TYPE_1__ linjs; } ;

/* Variables and functions */
 scalar_t__ ENODEV ; 
 scalar_t__ EV_ABS ; 
 scalar_t__ EV_KEY ; 
 scalar_t__ EV_SYN ; 
 scalar_t__ GLFW_FALSE ; 
 scalar_t__ GLFW_TRUE ; 
 scalar_t__ SYN_DROPPED ; 
 scalar_t__ SYN_REPORT ; 
 TYPE_9__ _glfw ; 
 int /*<<< orphan*/  closeJoystick (TYPE_3__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  handleAbsEvent (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handleKeyEvent (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pollAbsState (TYPE_3__*) ; 
 scalar_t__ read (int /*<<< orphan*/ ,struct input_event*,int) ; 

int _glfwPlatformPollJoystick(_GLFWjoystick* js, int mode)
{
    // Read all queued events (non-blocking)
    for (;;)
    {
        struct input_event e;

        errno = 0;
        if (read(js->linjs.fd, &e, sizeof(e)) < 0)
        {
            // Reset the joystick slot if the device was disconnected
            if (errno == ENODEV)
                closeJoystick(js);

            break;
        }

        if (e.type == EV_SYN)
        {
            if (e.code == SYN_DROPPED)
                _glfw.linjs.dropped = GLFW_TRUE;
            else if (e.code == SYN_REPORT)
            {
                _glfw.linjs.dropped = GLFW_FALSE;
                pollAbsState(js);
            }
        }

        if (_glfw.linjs.dropped)
            continue;

        if (e.type == EV_KEY)
            handleKeyEvent(js, e.code, e.value);
        else if (e.type == EV_ABS)
            handleAbsEvent(js, e.code, e.value);
    }

    return js->present;
}