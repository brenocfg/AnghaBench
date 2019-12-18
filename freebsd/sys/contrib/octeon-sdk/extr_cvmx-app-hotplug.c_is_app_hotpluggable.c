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
struct TYPE_3__ {scalar_t__ hotplug_activated_coremask; } ;
typedef  TYPE_1__ cvmx_app_hotplug_info_t ;

/* Variables and functions */
 TYPE_1__* cvmx_app_hotplug_get_info_at_index (int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int is_app_hotpluggable(int index)
{
    cvmx_app_hotplug_info_t *ai;

    if (!(ai = cvmx_app_hotplug_get_info_at_index(index)))
    {
        printf("\nERROR: Failed to get hotplug info for app at index=%d\n", index);
        return -1;
    }
    if (ai->hotplug_activated_coremask) return 1;
    return 0;
}