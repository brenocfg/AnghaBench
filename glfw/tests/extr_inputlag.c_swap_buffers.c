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
typedef  int /*<<< orphan*/  GLint ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_POINTS ; 
 int /*<<< orphan*/  GL_QUERY_RESULT ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_SAMPLES_PASSED ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  glBegin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBeginQuery (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnd () ; 
 int /*<<< orphan*/  glEndQuery (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glFinish () ; 
 int /*<<< orphan*/  glGenQueries (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetQueryObjectiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glReadPixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  glVertex2f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  occlusion_query ; 
 scalar_t__ swap_clear ; 
 scalar_t__ swap_finish ; 
 scalar_t__ swap_occlusion_query ; 
 scalar_t__ swap_read_pixels ; 

void swap_buffers(GLFWwindow* window)
{
    glfwSwapBuffers(window);

    if (swap_clear)
        glClear(GL_COLOR_BUFFER_BIT);

    if (swap_finish)
        glFinish();

    if (swap_occlusion_query) {
        GLint occlusion_result;
        if (!occlusion_query)
            glGenQueries(1, &occlusion_query);
        glBeginQuery(GL_SAMPLES_PASSED, occlusion_query);
        glBegin(GL_POINTS);
        glVertex2f(0, 0);
        glEnd();
        glEndQuery(GL_SAMPLES_PASSED);
        glGetQueryObjectiv(occlusion_query, GL_QUERY_RESULT, &occlusion_result);
    }

    if (swap_read_pixels) {
        unsigned char rgba[4];
        glReadPixels(0, 0, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, rgba);
    }
}