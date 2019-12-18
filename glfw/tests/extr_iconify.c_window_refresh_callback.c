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
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 double glfwGetTime () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,double) ; 

__attribute__((used)) static void window_refresh_callback(GLFWwindow* window)
{
    printf("%0.2f Window refresh\n", glfwGetTime());

    glfwMakeContextCurrent(window);

    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}