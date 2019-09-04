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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VkPhysicalDevice ;
typedef  int /*<<< orphan*/  VkInstance ;
struct TYPE_3__ {int /*<<< orphan*/  display; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;
typedef  int (* PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_API_UNAVAILABLE ; 
 int VK_NULL_HANDLE ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vkGetInstanceProcAddr (int /*<<< orphan*/ ,char*) ; 

int _glfwPlatformGetPhysicalDevicePresentationSupport(VkInstance instance,
                                                      VkPhysicalDevice device,
                                                      uint32_t queuefamily)
{
    PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR
        vkGetPhysicalDeviceWaylandPresentationSupportKHR =
        (PFN_vkGetPhysicalDeviceWaylandPresentationSupportKHR)
        vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceWaylandPresentationSupportKHR");
    if (!vkGetPhysicalDeviceWaylandPresentationSupportKHR)
    {
        _glfwInputError(GLFW_API_UNAVAILABLE,
                        "Wayland: Vulkan instance missing VK_KHR_wayland_surface extension");
        return VK_NULL_HANDLE;
    }

    return vkGetPhysicalDeviceWaylandPresentationSupportKHR(device,
                                                            queuefamily,
                                                            _glfw.wl.display);
}