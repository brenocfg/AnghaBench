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
struct demo {int /*<<< orphan*/  window; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_LONG_NAME ; 
 int /*<<< orphan*/  GLFW_CLIENT_API ; 
 int /*<<< orphan*/  GLFW_NO_API ; 
 int /*<<< orphan*/  demo_key_callback ; 
 int /*<<< orphan*/  demo_refresh_callback ; 
 int /*<<< orphan*/  demo_resize_callback ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwCreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowRefreshCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowUserPointer (int /*<<< orphan*/ ,struct demo*) ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void demo_create_window(struct demo *demo) {
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    demo->window = glfwCreateWindow(demo->width,
                                    demo->height,
                                    APP_LONG_NAME,
                                    NULL,
                                    NULL);
    if (!demo->window) {
        // It didn't work, so try to give a useful error:
        printf("Cannot create a window in which to draw!\n");
        fflush(stdout);
        exit(1);
    }

    glfwSetWindowUserPointer(demo->window, demo);
    glfwSetWindowRefreshCallback(demo->window, demo_refresh_callback);
    glfwSetFramebufferSizeCallback(demo->window, demo_resize_callback);
    glfwSetKeyCallback(demo->window, demo_key_callback);
}