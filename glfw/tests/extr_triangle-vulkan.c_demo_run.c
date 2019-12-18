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
struct demo {float depthStencil; float depthIncrement; scalar_t__ curFrame; scalar_t__ frameCount; int /*<<< orphan*/  window; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_TRUE ; 
 scalar_t__ INT32_MAX ; 
 int /*<<< orphan*/  demo_draw (struct demo*) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkDeviceWaitIdle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void demo_run(struct demo *demo) {
    while (!glfwWindowShouldClose(demo->window)) {
        glfwPollEvents();

        demo_draw(demo);

        if (demo->depthStencil > 0.99f)
            demo->depthIncrement = -0.001f;
        if (demo->depthStencil < 0.8f)
            demo->depthIncrement = 0.001f;

        demo->depthStencil += demo->depthIncrement;

        // Wait for work to finish before updating MVP.
        vkDeviceWaitIdle(demo->device);
        demo->curFrame++;
        if (demo->frameCount != INT32_MAX && demo->curFrame == demo->frameCount)
            glfwSetWindowShouldClose(demo->window, GLFW_TRUE);
    }
}