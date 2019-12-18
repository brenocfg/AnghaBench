#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ VkResult ;
struct TYPE_3__ {int /*<<< orphan*/  apiVersion; } ;
typedef  TYPE_1__ VkPhysicalDeviceProperties ;
typedef  int /*<<< orphan*/ * VkPhysicalDevice ;

/* Variables and functions */
 int GLAD_MAKE_VERSION (int,int) ; 
 int GLAD_VK_VERSION_1_0 ; 
 int GLAD_VK_VERSION_1_1 ; 
 scalar_t__ VK_SUCCESS ; 
 scalar_t__ VK_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ VK_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ vkEnumerateInstanceVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkGetPhysicalDeviceProperties (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int glad_vk_find_core_vulkan( VkPhysicalDevice physical_device) {
    int major = 1;
    int minor = 0;

#ifdef VK_VERSION_1_1
    if (vkEnumerateInstanceVersion  != NULL) {
        uint32_t version;
        VkResult result;

        result = vkEnumerateInstanceVersion(&version);
        if (result == VK_SUCCESS) {
            major = (int) VK_VERSION_MAJOR(version);
            minor = (int) VK_VERSION_MINOR(version);
        }
    }
#endif

    if (physical_device != NULL && vkGetPhysicalDeviceProperties  != NULL) {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(physical_device, &properties);

        major = (int) VK_VERSION_MAJOR(properties.apiVersion);
        minor = (int) VK_VERSION_MINOR(properties.apiVersion);
    }

    GLAD_VK_VERSION_1_0 = (major == 1 && minor >= 0) || major > 1;
    GLAD_VK_VERSION_1_1 = (major == 1 && minor >= 1) || major > 1;

    return GLAD_MAKE_VERSION(major, minor);
}