#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int app_shutdown; int coremask; int valid; void* hotplug_start; void* unplug_callback; void* cores_removed_callback; void* cores_added_callback; void* shutdown_callback; void* data; } ;
typedef  TYPE_1__ cvmx_app_hotplug_info_t ;
struct TYPE_8__ {void* shutdown_callback; void* cores_added_callback; void* cores_removed_callback; void* unplug_core_callback; void* hotplug_start; } ;
typedef  TYPE_2__ cvmx_app_hotplug_callbacks_t ;
struct TYPE_9__ {int /*<<< orphan*/  core_mask; } ;

/* Variables and functions */
 void* CAST64 (void*) ; 
 int /*<<< orphan*/  CVMX_IRQ_MBOX0 ; 
 int /*<<< orphan*/  __cvmx_app_hotplug_shutdown ; 
 TYPE_1__* cvmx_app_hotplug_get_info (int /*<<< orphan*/ ) ; 
 TYPE_1__* cvmx_app_hotplug_info_ptr ; 
 int /*<<< orphan*/  cvmx_interrupt_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int cvmx_app_hotplug_register_cb(cvmx_app_hotplug_callbacks_t *cb, void* arg,
                                 int app_shutdown)
{
    cvmx_app_hotplug_info_t *app_info;

    /* Find the list of applications launched by bootoct utility. */
    app_info = cvmx_app_hotplug_get_info(cvmx_sysinfo_get()->core_mask);
    cvmx_app_hotplug_info_ptr = app_info;
    if (!app_info)
    {
        /* Application not launched by bootoct? */
        printf("ERROR: cmvx_app_hotplug_register() failed\n");
        return -1;
    }
    /* Register the callback */
    app_info->data = CAST64(arg);
    app_info->shutdown_callback  = CAST64(cb->shutdown_callback);
    app_info->cores_added_callback = CAST64(cb->cores_added_callback);
    app_info->cores_removed_callback = CAST64(cb->cores_removed_callback);
    app_info->unplug_callback = CAST64(cb->unplug_core_callback);
    app_info->hotplug_start = CAST64(cb->hotplug_start);
    app_info->app_shutdown = app_shutdown;
#ifdef DEBUG
    printf("cvmx_app_hotplug_register(): coremask 0x%x valid %d\n",
           app_info->coremask, app_info->valid);
#endif

    cvmx_interrupt_register(CVMX_IRQ_MBOX0, __cvmx_app_hotplug_shutdown, NULL);
    return 0;

}