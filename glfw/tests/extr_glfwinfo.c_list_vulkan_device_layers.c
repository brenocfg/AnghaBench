#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  VkPhysicalDevice ;
struct TYPE_5__ {char* layerName; int specVersion; char* description; } ;
typedef  TYPE_1__ VkLayerProperties ;
typedef  int /*<<< orphan*/  VkInstance ;

/* Variables and functions */
 TYPE_1__* calloc (size_t,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  vkEnumerateDeviceLayerProperties (int /*<<< orphan*/ ,size_t*,TYPE_1__*) ; 

__attribute__((used)) static void list_vulkan_device_layers(VkInstance instance, VkPhysicalDevice device)
{
    printf("Vulkan device layers:\n");

    uint32_t lp_count;
    vkEnumerateDeviceLayerProperties(device, &lp_count, NULL);
    VkLayerProperties* lp = calloc(lp_count, sizeof(VkLayerProperties));
    vkEnumerateDeviceLayerProperties(device, &lp_count, lp);

    for (uint32_t i = 0;  i < lp_count;  i++)
    {
        printf(" %s (spec version %u) \"%s\"\n",
               lp[i].layerName,
               lp[i].specVersion >> 22,
               lp[i].description);
    }

    free(lp);
}