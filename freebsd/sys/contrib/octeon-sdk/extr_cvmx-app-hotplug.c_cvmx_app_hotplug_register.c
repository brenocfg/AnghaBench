#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int coremask; int valid; void* shutdown_callback; void* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  core_mask; } ;

/* Variables and functions */
 void* CAST64 (void (*) (void*)) ; 
 int /*<<< orphan*/  CVMX_IRQ_MBOX0 ; 
 int /*<<< orphan*/  __cvmx_app_hotplug_shutdown ; 
 TYPE_2__* cvmx_app_hotplug_get_info (int /*<<< orphan*/ ) ; 
 TYPE_2__* cvmx_app_hotplug_info_ptr ; 
 int /*<<< orphan*/  cvmx_interrupt_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int cvmx_app_hotplug_register(void(*fn)(void*), void* arg)
{
    /* Find the list of applications launched by bootoct utility. */

    if (!(cvmx_app_hotplug_info_ptr = cvmx_app_hotplug_get_info(cvmx_sysinfo_get()->core_mask)))
    {
        /* Application not launched by bootoct? */
        printf("ERROR: cmvx_app_hotplug_register() failed\n");
        return -1;
    }

    /* Register the callback */
    cvmx_app_hotplug_info_ptr->data = CAST64(arg);
    cvmx_app_hotplug_info_ptr->shutdown_callback = CAST64(fn);

#ifdef DEBUG
    printf("cvmx_app_hotplug_register(): coremask 0x%x valid %d\n", 
                  cvmx_app_hotplug_info_ptr->coremask, cvmx_app_hotplug_info_ptr->valid);
#endif

    cvmx_interrupt_register(CVMX_IRQ_MBOX0, __cvmx_app_hotplug_shutdown, NULL);

    return 0;
}