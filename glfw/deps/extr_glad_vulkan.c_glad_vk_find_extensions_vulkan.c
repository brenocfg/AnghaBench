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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  VkPhysicalDevice ;

/* Variables and functions */
 void* GLAD_VK_EXT_debug_report ; 
 void* GLAD_VK_KHR_surface ; 
 void* GLAD_VK_KHR_swapchain ; 
 int /*<<< orphan*/  glad_vk_free_extensions (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  glad_vk_get_extensions (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char***) ; 
 void* glad_vk_has_extension (char*,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int glad_vk_find_extensions_vulkan( VkPhysicalDevice physical_device) {
    uint32_t extension_count = 0;
    char **extensions = NULL;
    if (!glad_vk_get_extensions(physical_device, &extension_count, &extensions)) return 0;

    GLAD_VK_EXT_debug_report = glad_vk_has_extension("VK_EXT_debug_report", extension_count, extensions);
    GLAD_VK_KHR_surface = glad_vk_has_extension("VK_KHR_surface", extension_count, extensions);
    GLAD_VK_KHR_swapchain = glad_vk_has_extension("VK_KHR_swapchain", extension_count, extensions);

    glad_vk_free_extensions(extension_count, extensions);

    return 1;
}