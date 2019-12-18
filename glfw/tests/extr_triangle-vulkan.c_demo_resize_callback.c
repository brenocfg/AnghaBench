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
struct demo {int width; int height; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  demo_resize (struct demo*) ; 
 struct demo* glfwGetWindowUserPointer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void demo_resize_callback(GLFWwindow* window, int width, int height) {
    struct demo* demo = glfwGetWindowUserPointer(window);
    demo->width = width;
    demo->height = height;
    demo_resize(demo);
}