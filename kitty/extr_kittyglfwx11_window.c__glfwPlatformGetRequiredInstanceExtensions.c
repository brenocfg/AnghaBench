#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ KHR_xcb_surface; int /*<<< orphan*/  KHR_xlib_surface; int /*<<< orphan*/  KHR_surface; } ;
struct TYPE_4__ {TYPE_1__ vk; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 

void _glfwPlatformGetRequiredInstanceExtensions(char** extensions)
{
    if (!_glfw.vk.KHR_surface)
        return;

    if (!_glfw.vk.KHR_xcb_surface)
    {
        if (!_glfw.vk.KHR_xlib_surface)
            return;
    }

    extensions[0] = "VK_KHR_surface";

    // NOTE: VK_KHR_xcb_surface is preferred due to some early ICDs exposing but
    //       not correctly implementing VK_KHR_xlib_surface
    if (_glfw.vk.KHR_xcb_surface)
        extensions[1] = "VK_KHR_xcb_surface";
    else
        extensions[1] = "VK_KHR_xlib_surface";
}