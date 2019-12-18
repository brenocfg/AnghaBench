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
typedef  scalar_t__ VkPhysicalDeviceType ;

/* Variables and functions */
 scalar_t__ VK_PHYSICAL_DEVICE_TYPE_CPU ; 
 scalar_t__ VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ; 
 scalar_t__ VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU ; 
 scalar_t__ VK_PHYSICAL_DEVICE_TYPE_OTHER ; 
 scalar_t__ VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU ; 

__attribute__((used)) static const char* get_device_type_name(VkPhysicalDeviceType type)
{
    if (type == VK_PHYSICAL_DEVICE_TYPE_OTHER)
        return "other";
    else if (type == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
        return "integrated GPU";
    else if (type == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        return "discrete GPU";
    else if (type == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)
        return "virtual GPU";
    else if (type == VK_PHYSICAL_DEVICE_TYPE_CPU)
        return "CPU";

    return "unknown";
}