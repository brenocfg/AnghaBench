#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VkPhysicalDevice ;
typedef  int /*<<< orphan*/  VkInstance ;
typedef  int /*<<< orphan*/  VisualID ;
struct TYPE_5__ {scalar_t__ handle; } ;
struct TYPE_6__ {int /*<<< orphan*/  display; TYPE_1__ x11xcb; int /*<<< orphan*/  screen; } ;
struct TYPE_7__ {scalar_t__ KHR_xcb_surface; } ;
struct TYPE_8__ {TYPE_2__ x11; TYPE_3__ vk; } ;
typedef  int (* PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  int (* PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultVisual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLFW_API_UNAVAILABLE ; 
 int GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/ * XGetXCBConnection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVisualIDFromVisual (int /*<<< orphan*/ ) ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vkGetInstanceProcAddr (int /*<<< orphan*/ ,char*) ; 

int _glfwPlatformGetPhysicalDevicePresentationSupport(VkInstance instance,
                                                      VkPhysicalDevice device,
                                                      uint32_t queuefamily)
{
    VisualID visualID = XVisualIDFromVisual(DefaultVisual(_glfw.x11.display,
                                                          _glfw.x11.screen));

    if (_glfw.vk.KHR_xcb_surface && _glfw.x11.x11xcb.handle)
    {
        PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR
            vkGetPhysicalDeviceXcbPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXcbPresentationSupportKHR)
            vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceXcbPresentationSupportKHR");
        if (!vkGetPhysicalDeviceXcbPresentationSupportKHR)
        {
            _glfwInputError(GLFW_API_UNAVAILABLE,
                            "X11: Vulkan instance missing VK_KHR_xcb_surface extension");
            return GLFW_FALSE;
        }

        xcb_connection_t* connection = XGetXCBConnection(_glfw.x11.display);
        if (!connection)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "X11: Failed to retrieve XCB connection");
            return GLFW_FALSE;
        }

        return vkGetPhysicalDeviceXcbPresentationSupportKHR(device,
                                                            queuefamily,
                                                            connection,
                                                            visualID);
    }
    else
    {
        PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR
            vkGetPhysicalDeviceXlibPresentationSupportKHR =
            (PFN_vkGetPhysicalDeviceXlibPresentationSupportKHR)
            vkGetInstanceProcAddr(instance, "vkGetPhysicalDeviceXlibPresentationSupportKHR");
        if (!vkGetPhysicalDeviceXlibPresentationSupportKHR)
        {
            _glfwInputError(GLFW_API_UNAVAILABLE,
                            "X11: Vulkan instance missing VK_KHR_xlib_surface extension");
            return GLFW_FALSE;
        }

        return vkGetPhysicalDeviceXlibPresentationSupportKHR(device,
                                                             queuefamily,
                                                             _glfw.x11.display,
                                                             visualID);
    }
}