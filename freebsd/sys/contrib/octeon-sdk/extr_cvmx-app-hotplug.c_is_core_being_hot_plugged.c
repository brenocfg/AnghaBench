#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long long hplugged_cores; } ;

/* Variables and functions */
 TYPE_1__* cvmx_app_hotplug_info_ptr ; 
 unsigned long long cvmx_get_core_num () ; 

int is_core_being_hot_plugged(void)
{

#ifndef CVMX_BUILD_FOR_LINUX_USER
    if (!cvmx_app_hotplug_info_ptr) return 0;
    if (cvmx_app_hotplug_info_ptr->hplugged_cores &
        (1ull << cvmx_get_core_num()))
        return 1;
    return 0;
#else
    return 0;
#endif
}