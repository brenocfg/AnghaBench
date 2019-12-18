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
typedef  int /*<<< orphan*/  VkPhysicalDevice ;
typedef  scalar_t__ PFN_vkEnumerateInstanceVersion ;
typedef  scalar_t__ (* GLADuserptrloadfunc ) (char*,void*) ;

/* Variables and functions */
 int glad_vk_find_core_vulkan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glad_vk_find_extensions_vulkan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glad_vk_load_VK_EXT_debug_report (scalar_t__ (*) (char*,void*),void*) ; 
 int /*<<< orphan*/  glad_vk_load_VK_KHR_surface (scalar_t__ (*) (char*,void*),void*) ; 
 int /*<<< orphan*/  glad_vk_load_VK_KHR_swapchain (scalar_t__ (*) (char*,void*),void*) ; 
 int /*<<< orphan*/  glad_vk_load_VK_VERSION_1_0 (scalar_t__ (*) (char*,void*),void*) ; 
 int /*<<< orphan*/  glad_vk_load_VK_VERSION_1_1 (scalar_t__ (*) (char*,void*),void*) ; 
 scalar_t__ vkEnumerateInstanceVersion ; 

int gladLoadVulkanUserPtr( VkPhysicalDevice physical_device, GLADuserptrloadfunc load, void *userptr) {
    int version;

#ifdef VK_VERSION_1_1
    vkEnumerateInstanceVersion  = (PFN_vkEnumerateInstanceVersion) load("vkEnumerateInstanceVersion", userptr);
#endif
    version = glad_vk_find_core_vulkan( physical_device);
    if (!version) {
        return 0;
    }

    glad_vk_load_VK_VERSION_1_0(load, userptr);
    glad_vk_load_VK_VERSION_1_1(load, userptr);

    if (!glad_vk_find_extensions_vulkan( physical_device)) return 0;
    glad_vk_load_VK_EXT_debug_report(load, userptr);
    glad_vk_load_VK_KHR_surface(load, userptr);
    glad_vk_load_VK_KHR_swapchain(load, userptr);


    return version;
}