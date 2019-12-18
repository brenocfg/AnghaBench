#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int buttonCount; int hatCount; unsigned char const* buttons; int /*<<< orphan*/  present; } ;
typedef  TYPE_3__ _GLFWjoystick ;
struct TYPE_6__ {scalar_t__ hatButtons; } ;
struct TYPE_7__ {TYPE_1__ init; } ;
struct TYPE_9__ {TYPE_2__ hints; TYPE_3__* joysticks; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
 int GLFW_JOYSTICK_1 ; 
 int GLFW_JOYSTICK_LAST ; 
 int /*<<< orphan*/  _GLFW_POLL_BUTTONS ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int /*<<< orphan*/ *) ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  _glfwPlatformPollJoystick (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

const unsigned char* glfwGetJoystickButtons(int jid, int* count)
{
    _GLFWjoystick* js;

    assert(jid >= GLFW_JOYSTICK_1);
    assert(jid <= GLFW_JOYSTICK_LAST);
    assert(count != NULL);

    *count = 0;

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    if (jid < 0 || jid > GLFW_JOYSTICK_LAST)
    {
        _glfwInputError(GLFW_INVALID_ENUM, "Invalid joystick ID %i", jid);
        return NULL;
    }

    js = _glfw.joysticks + jid;
    if (!js->present)
        return NULL;

    if (!_glfwPlatformPollJoystick(js, _GLFW_POLL_BUTTONS))
        return NULL;

    if (_glfw.hints.init.hatButtons)
        *count = js->buttonCount + js->hatCount * 4;
    else
        *count = js->buttonCount;

    return js->buttons;
}