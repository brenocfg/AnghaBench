#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  core_mask; } ;
typedef  TYPE_1__ cvmx_sysinfo_t ;
struct TYPE_6__ {int shutdown_done; scalar_t__ shutdown_cores; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cvmx_app_hotplug_reset () ; 
 int /*<<< orphan*/  __cvmx_app_hotplug_sync () ; 
 int /*<<< orphan*/  bzero (TYPE_3__*,int) ; 
 TYPE_3__* cvmx_app_hotplug_info_ptr ; 
 int /*<<< orphan*/  cvmx_app_hotplug_remove_self_from_core_mask () ; 
 scalar_t__ cvmx_coremask_first_core (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_debug_finish () ; 
 int /*<<< orphan*/  cvmx_interrupt_disable_save () ; 
 TYPE_1__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_sysinfo_remove_self_from_core_mask () ; 
 int /*<<< orphan*/  printf (char*) ; 

void cvmx_app_hotplug_core_shutdown(void)
{
    uint32_t flags;
    if (cvmx_app_hotplug_info_ptr->shutdown_cores)
    {
        cvmx_sysinfo_t *sys_info_ptr = cvmx_sysinfo_get();
       __cvmx_app_hotplug_sync();
        if (cvmx_coremask_first_core(sys_info_ptr->core_mask))
        {
            bzero(cvmx_app_hotplug_info_ptr,
                  sizeof(*cvmx_app_hotplug_info_ptr));
            #ifdef DEBUG
            printf("__cvmx_app_hotplug_shutdown(): setting shutdown done! \n");
            #endif
            cvmx_app_hotplug_info_ptr->shutdown_done = 1;
        }
        /* Tell the debugger that this application is finishing.  */
        cvmx_debug_finish ();
        flags = cvmx_interrupt_disable_save();
        __cvmx_app_hotplug_sync();
        /* Reset the core */
        __cvmx_app_hotplug_reset();
    }
    else
    {
        cvmx_sysinfo_remove_self_from_core_mask();
        cvmx_app_hotplug_remove_self_from_core_mask();
        flags = cvmx_interrupt_disable_save();
        __cvmx_app_hotplug_reset();
    }
}