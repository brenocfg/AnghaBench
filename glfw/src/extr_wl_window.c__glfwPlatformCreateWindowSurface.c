#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sci ;
struct TYPE_10__ {int /*<<< orphan*/  surface; } ;
struct TYPE_11__ {TYPE_2__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_12__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  display; int /*<<< orphan*/  sType; } ;
typedef  TYPE_4__ VkWaylandSurfaceCreateInfoKHR ;
typedef  int /*<<< orphan*/  VkSurfaceKHR ;
typedef  scalar_t__ VkResult ;
typedef  int /*<<< orphan*/  VkInstance ;
typedef  int /*<<< orphan*/  VkAllocationCallbacks ;
struct TYPE_9__ {int /*<<< orphan*/  display; } ;
struct TYPE_13__ {TYPE_1__ wl; } ;
typedef  scalar_t__ (* PFN_vkCreateWaylandSurfaceKHR ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_API_UNAVAILABLE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 scalar_t__ VK_ERROR_EXTENSION_NOT_PRESENT ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR ; 
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  _glfwGetVulkanResultString (scalar_t__) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ vkGetInstanceProcAddr (int /*<<< orphan*/ ,char*) ; 

VkResult _glfwPlatformCreateWindowSurface(VkInstance instance,
                                          _GLFWwindow* window,
                                          const VkAllocationCallbacks* allocator,
                                          VkSurfaceKHR* surface)
{
    VkResult err;
    VkWaylandSurfaceCreateInfoKHR sci;
    PFN_vkCreateWaylandSurfaceKHR vkCreateWaylandSurfaceKHR;

    vkCreateWaylandSurfaceKHR = (PFN_vkCreateWaylandSurfaceKHR)
        vkGetInstanceProcAddr(instance, "vkCreateWaylandSurfaceKHR");
    if (!vkCreateWaylandSurfaceKHR)
    {
        _glfwInputError(GLFW_API_UNAVAILABLE,
                        "Wayland: Vulkan instance missing VK_KHR_wayland_surface extension");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    memset(&sci, 0, sizeof(sci));
    sci.sType = VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
    sci.display = _glfw.wl.display;
    sci.surface = window->wl.surface;

    err = vkCreateWaylandSurfaceKHR(instance, &sci, allocator, surface);
    if (err)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Failed to create Vulkan surface: %s",
                        _glfwGetVulkanResultString(err));
    }

    return err;
}