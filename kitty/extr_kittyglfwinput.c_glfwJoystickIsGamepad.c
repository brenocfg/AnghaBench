#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * mapping; int /*<<< orphan*/  present; } ;
typedef  TYPE_1__ _GLFWjoystick ;
struct TYPE_5__ {TYPE_1__* joysticks; } ;

/* Variables and functions */
 int GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
 int GLFW_JOYSTICK_1 ; 
 int GLFW_JOYSTICK_LAST ; 
 int /*<<< orphan*/  _GLFW_POLL_PRESENCE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int) ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  _glfwPlatformPollJoystick (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

int glfwJoystickIsGamepad(int jid)
{
    _GLFWjoystick* js;

    assert(jid >= GLFW_JOYSTICK_1);
    assert(jid <= GLFW_JOYSTICK_LAST);

    _GLFW_REQUIRE_INIT_OR_RETURN(GLFW_FALSE);

    if (jid < 0 || jid > GLFW_JOYSTICK_LAST)
    {
        _glfwInputError(GLFW_INVALID_ENUM, "Invalid joystick ID %i", jid);
        return GLFW_FALSE;
    }

    js = _glfw.joysticks + jid;
    if (!js->present)
        return GLFW_FALSE;

    if (!_glfwPlatformPollJoystick(js, _GLFW_POLL_PRESENCE))
        return GLFW_FALSE;

    return js->mapping != NULL;
}