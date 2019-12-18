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
struct TYPE_5__ {scalar_t__ type; int index; } ;
typedef  TYPE_1__ _GLFWmapelement ;
struct TYPE_6__ {int hatCount; int buttonCount; int axisCount; } ;
typedef  TYPE_2__ _GLFWjoystick ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 scalar_t__ _GLFW_JOYSTICK_AXIS ; 
 scalar_t__ _GLFW_JOYSTICK_BUTTON ; 
 scalar_t__ _GLFW_JOYSTICK_HATBIT ; 

__attribute__((used)) static GLFWbool isValidElementForJoystick(const _GLFWmapelement* e,
                                          const _GLFWjoystick* js)
{
    if (e->type == _GLFW_JOYSTICK_HATBIT && (e->index >> 4) >= js->hatCount)
        return GLFW_FALSE;
    else if (e->type == _GLFW_JOYSTICK_BUTTON && e->index >= js->buttonCount)
        return GLFW_FALSE;
    else if (e->type == _GLFW_JOYSTICK_AXIS && e->index >= js->axisCount)
        return GLFW_FALSE;

    return GLFW_TRUE;
}