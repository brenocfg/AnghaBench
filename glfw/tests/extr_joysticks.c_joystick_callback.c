#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int GLFW_CONNECTED ; 
 int GLFW_DISCONNECTED ; 
 int /*<<< orphan*/  GLFW_FOCUSED ; 
 int /*<<< orphan*/  glfwGetWindowAttrib (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwRequestWindowAttention (int /*<<< orphan*/ ) ; 
 int joystick_count ; 
 int* joysticks ; 
 int /*<<< orphan*/  window ; 

__attribute__((used)) static void joystick_callback(int jid, int event)
{
    if (event == GLFW_CONNECTED)
        joysticks[joystick_count++] = jid;
    else if (event == GLFW_DISCONNECTED)
    {
        int i;

        for (i = 0;  i < joystick_count;  i++)
        {
            if (joysticks[i] == jid)
                break;
        }

        for (i = i + 1;  i < joystick_count;  i++)
            joysticks[i - 1] = joysticks[i];

        joystick_count--;
    }

    if (!glfwGetWindowAttrib(window, GLFW_FOCUSED))
        glfwRequestWindowAttention(window);
}