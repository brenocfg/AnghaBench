#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ valid; } ;
typedef  TYPE_1__ cvmx_app_hotplug_info_t ;
struct TYPE_8__ {TYPE_1__* hotplug_info_array; } ;
typedef  TYPE_2__ cvmx_app_hotplug_global_t ;
struct TYPE_9__ {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int CVMX_APP_HOTPLUG_MAX_APPS ; 
 TYPE_6__* block_desc ; 
 TYPE_2__* cvmx_app_get_hotplug_global_ptr () ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 

cvmx_app_hotplug_info_t* cvmx_app_hotplug_get_info_at_index(int index)
{
    cvmx_app_hotplug_info_t *hip;
    cvmx_app_hotplug_global_t *hgp;

    hgp = cvmx_app_get_hotplug_global_ptr();
    if (!hgp) return NULL;
    hip = hgp->hotplug_info_array;

#ifdef DEBUG
    printf("cvmx_app_hotplug_get_info(): hotplug_info phy addr 0x%llx ptr %p\n", 
                  block_desc->base_addr, hgp);
#endif
    if (index < CVMX_APP_HOTPLUG_MAX_APPS)
    {
        if (hip[index].valid) 
        {
            //print_hot_plug_info( &hip[index] );
            return &hip[index];
        }
    }
    return NULL;
}