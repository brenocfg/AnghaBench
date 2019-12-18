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
struct nk_rect {int dummy; } ;
struct nk_font_atlas {int dummy; } ;
struct nk_context {int dummy; } ;
struct TYPE_4__ {int size; void* blue; void* green; void* red; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWmonitor ;
typedef  TYPE_1__ GLFWgammaramp ;

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
 int /*<<< orphan*/  chart_ramp_array (struct nk_context*,int /*<<< orphan*/ ,int,void*) ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gladLoadGL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* glfwGetGammaRamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 int /*<<< orphan*/  glfwGetProcAddress ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetGamma (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  glfwSetGammaRamp (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWaitEventsTimeout (double) ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_callback ; 
 void* malloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t const) ; 
 scalar_t__ nk_begin (struct nk_context*,char*,struct nk_rect,int /*<<< orphan*/ ) ; 
 scalar_t__ nk_button_label (struct nk_context*,char*) ; 
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
 int /*<<< orphan*/  nk_rgb (int,int,int) ; 
 scalar_t__ nk_slider_float (struct nk_context*,float,float*,float,float) ; 
 int /*<<< orphan*/  nk_window_set_bounds (struct nk_context*,char*,struct nk_rect) ; 

int main(int argc, char** argv)
{
    GLFWmonitor* monitor = NULL;
    GLFWwindow* window;
    GLFWgammaramp orig_ramp;
    struct nk_context* nk;
    struct nk_font_atlas* atlas;
    float gamma_value = 1.f;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    monitor = glfwGetPrimaryMonitor();

    glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
    glfwWindowHint(GLFW_WIN32_KEYBOARD_MENU, GLFW_TRUE);

    window = glfwCreateWindow(800, 400, "Gamma Test", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    {
        const GLFWgammaramp* ramp = glfwGetGammaRamp(monitor);
        const size_t array_size = ramp->size * sizeof(short);
        orig_ramp.size = ramp->size;
        orig_ramp.red = malloc(array_size);
        orig_ramp.green = malloc(array_size);
        orig_ramp.blue = malloc(array_size);
        memcpy(orig_ramp.red, ramp->red, array_size);
        memcpy(orig_ramp.green, ramp->green, array_size);
        memcpy(orig_ramp.blue, ramp->blue, array_size);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    nk = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();

    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        struct nk_rect area;

        glfwGetWindowSize(window, &width, &height);
        area = nk_rect(0.f, 0.f, (float) width, (float) height);
        nk_window_set_bounds(nk, "", area);

        glClear(GL_COLOR_BUFFER_BIT);
        nk_glfw3_new_frame();
        if (nk_begin(nk, "", area, 0))
        {
            const GLFWgammaramp* ramp;

            nk_layout_row_dynamic(nk, 30, 3);
            if (nk_slider_float(nk, 0.1f, &gamma_value, 5.f, 0.1f))
                glfwSetGamma(monitor, gamma_value);
            nk_labelf(nk, NK_TEXT_LEFT, "%0.1f", gamma_value);
            if (nk_button_label(nk, "Revert"))
                glfwSetGammaRamp(monitor, &orig_ramp);

            ramp = glfwGetGammaRamp(monitor);

            nk_layout_row_dynamic(nk, height - 60.f, 3);
            chart_ramp_array(nk, nk_rgb(255, 0, 0), ramp->size, ramp->red);
            chart_ramp_array(nk, nk_rgb(0, 255, 0), ramp->size, ramp->green);
            chart_ramp_array(nk, nk_rgb(0, 0, 255), ramp->size, ramp->blue);
        }

        nk_end(nk);
        nk_glfw3_render(NK_ANTI_ALIASING_ON);

        glfwSwapBuffers(window);
        glfwWaitEventsTimeout(1.0);
    }

    free(orig_ramp.red);
    free(orig_ramp.green);
    free(orig_ramp.blue);

    nk_glfw3_shutdown();
    glfwTerminate();
    exit(EXIT_SUCCESS);
}