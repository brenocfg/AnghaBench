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
struct nk_rect {int dummy; } ;
struct nk_font_atlas {int dummy; } ;
struct nk_context {int dummy; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GLFW_SCALE_TO_MONITOR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  GLFW_WIN32_KEYBOARD_MENU ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  NK_ANTI_ALIASING_ON ; 
 int /*<<< orphan*/  NK_GLFW3_INSTALL_CALLBACKS ; 
 int /*<<< orphan*/  NK_TEXT_LEFT ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gladLoadGL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetProcAddress ; 
 float glfwGetWindowOpacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowOpacity (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWaitEventsTimeout (double) ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 scalar_t__ nk_begin (struct nk_context*,char*,struct nk_rect,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_end (struct nk_context*) ; 
 int /*<<< orphan*/  nk_glfw3_font_stash_begin (struct nk_font_atlas**) ; 
 int /*<<< orphan*/  nk_glfw3_font_stash_end () ; 
 struct nk_context* nk_glfw3_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_glfw3_new_frame () ; 
 int /*<<< orphan*/  nk_glfw3_render (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nk_glfw3_shutdown () ; 
 int /*<<< orphan*/  nk_labelf (struct nk_context*,int /*<<< orphan*/ ,char*,float) ; 
 int /*<<< orphan*/  nk_layout_row_dynamic (struct nk_context*,int,int) ; 
 struct nk_rect nk_rect (float,float,float,float) ; 
 scalar_t__ nk_slider_float (struct nk_context*,float,float*,float,float) ; 

int main(int argc, char** argv)
{
    GLFWwindow* window;
    struct nk_context* nk;
    struct nk_font_atlas* atlas;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_WIN32_KEYBOARD_MENU, GLFW_TRUE);

    window = glfwCreateWindow(400, 400, "Opacity", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    nk = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        struct nk_rect area;

        glfwGetWindowSize(window, &width, &height);
        area = nk_rect(0.f, 0.f, (float) width, (float) height);

        glClear(GL_COLOR_BUFFER_BIT);
        nk_glfw3_new_frame();
        if (nk_begin(nk, "", area, 0))
        {
            float opacity = glfwGetWindowOpacity(window);
            nk_layout_row_dynamic(nk, 30, 2);
            if (nk_slider_float(nk, 0.f, &opacity, 1.f, 0.001f))
                glfwSetWindowOpacity(window, opacity);
            nk_labelf(nk, NK_TEXT_LEFT, "%0.3f", opacity);
        }

        nk_end(nk);
        nk_glfw3_render(NK_ANTI_ALIASING_ON);

        glfwSwapBuffers(window);
        glfwWaitEventsTimeout(1.0);
    }

    nk_glfw3_shutdown();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}