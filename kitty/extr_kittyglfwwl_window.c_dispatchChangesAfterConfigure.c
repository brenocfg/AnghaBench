#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32_t ;
struct TYPE_10__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  scale; } ;
struct TYPE_11__ {TYPE_1__ wl; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  _glfwInputWindowContentScale (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputWindowDamage (TYPE_2__*) ; 
 int /*<<< orphan*/  _glfwInputWindowSize (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowSize (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int checkScaleChange (TYPE_2__*) ; 
 int /*<<< orphan*/  resizeFramebuffer (TYPE_2__*) ; 

__attribute__((used)) static void dispatchChangesAfterConfigure(_GLFWwindow *window, int32_t width, int32_t height) {
    if (width <= 0) width = window->wl.width;
    if (height <= 0) height = window->wl.height;
    GLFWbool size_changed = width != window->wl.width || height != window->wl.height;
    GLFWbool scale_changed = checkScaleChange(window);

    if (size_changed) {
        _glfwInputWindowSize(window, width, height);
        _glfwPlatformSetWindowSize(window, width, height);
    }

    if (scale_changed) {
        if (!size_changed)
            resizeFramebuffer(window);
        _glfwInputWindowContentScale(window, window->wl.scale, window->wl.scale);
    }

    _glfwInputWindowDamage(window);
}