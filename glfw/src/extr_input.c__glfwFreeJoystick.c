#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hats; int /*<<< orphan*/  buttons; int /*<<< orphan*/  axes; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ _GLFWjoystick ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void _glfwFreeJoystick(_GLFWjoystick* js)
{
    free(js->name);
    free(js->axes);
    free(js->buttons);
    free(js->hats);
    memset(js, 0, sizeof(_GLFWjoystick));
}