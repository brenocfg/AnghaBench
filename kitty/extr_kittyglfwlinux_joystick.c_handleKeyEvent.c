#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * keyMap; } ;
struct TYPE_6__ {TYPE_1__ linjs; } ;
typedef  TYPE_2__ _GLFWjoystick ;

/* Variables and functions */
 int BTN_MISC ; 
 int /*<<< orphan*/  GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_RELEASE ; 
 int /*<<< orphan*/  _glfwInputJoystickButton (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handleKeyEvent(_GLFWjoystick* js, int code, int value)
{
    _glfwInputJoystickButton(js,
                             js->linjs.keyMap[code - BTN_MISC],
                             value ? GLFW_PRESS : GLFW_RELEASE);
}