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
typedef  scalar_t__ VkPhysicalDevice ;
typedef  scalar_t__ VkInstance ;
struct TYPE_3__ {int /*<<< orphan*/ * extensions; } ;
struct TYPE_4__ {TYPE_1__ vk; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_API_UNAVAILABLE ; 
 int GLFW_FALSE ; 
 scalar_t__ VK_NULL_HANDLE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int) ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_LOADER ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInitVulkan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int _glfwPlatformGetPhysicalDevicePresentationSupport (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

int glfwGetPhysicalDevicePresentationSupport(VkInstance instance,
                                                     VkPhysicalDevice device,
                                                     uint32_t queuefamily)
{
    assert(instance != VK_NULL_HANDLE);
    assert(device != VK_NULL_HANDLE);

    _GLFW_REQUIRE_INIT_OR_RETURN(GLFW_FALSE);

    if (!_glfwInitVulkan(_GLFW_REQUIRE_LOADER))
        return GLFW_FALSE;

    if (!_glfw.vk.extensions[0])
    {
        _glfwInputError(GLFW_API_UNAVAILABLE,
                        "Vulkan: Window surface creation extensions not found");
        return GLFW_FALSE;
    }

    return _glfwPlatformGetPhysicalDevicePresentationSupport(instance,
                                                             device,
                                                             queuefamily);
}