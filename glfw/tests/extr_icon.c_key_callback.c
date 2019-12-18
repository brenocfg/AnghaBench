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
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
#define  GLFW_KEY_ESCAPE 130 
#define  GLFW_KEY_SPACE 129 
#define  GLFW_KEY_X 128 
 int GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int cur_icon_color ; 
 int /*<<< orphan*/  glfwSetWindowIcon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_icon (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_SPACE:
            cur_icon_color = (cur_icon_color + 1) % 5;
            set_icon(window, cur_icon_color);
            break;
        case GLFW_KEY_X:
            glfwSetWindowIcon(window, 0, NULL);
            break;
    }
}