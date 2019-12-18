#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long uint32_t ;
struct TYPE_4__ {unsigned long long shutdown_cores; unsigned long long hotplug_activated_coremask; int /*<<< orphan*/  shutdown_done; int /*<<< orphan*/  shutdown_callback; } ;
typedef  TYPE_1__ cvmx_app_hotplug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_MBOX_SETX (int) ; 
 int CVMX_MAX_CORES ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 TYPE_1__* cvmx_app_hotplug_get_info (unsigned long long) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int cvmx_app_hotplug_shutdown_request(uint32_t coremask, int wait) 
{
    int i;
    cvmx_app_hotplug_info_t *hotplug_info_ptr;

    if (!(hotplug_info_ptr = cvmx_app_hotplug_get_info(coremask)))
    {
        printf("\nERROR: Failed to get hotplug info for coremask: 0x%x\n", (unsigned int)coremask);
        return -1;
    }
    hotplug_info_ptr->shutdown_cores = coremask;
    if (!hotplug_info_ptr->shutdown_callback)
    {
        printf("\nERROR: Target application has not registered for hotplug!\n");
        return -1;
    }

    if (hotplug_info_ptr->hotplug_activated_coremask != coremask)
    {
        printf("\nERROR: Not all application cores have activated hotplug\n");
        return -1;
    }

    /* Send IPIs to all application cores to request shutdown */
    for (i=0; i<CVMX_MAX_CORES; i++) {
            if (coremask & (1ull<<i))
                cvmx_write_csr(CVMX_CIU_MBOX_SETX(i), 1);
    }

    if (wait)
    {
        while (!hotplug_info_ptr->shutdown_done);    

        /* Clean up the hotplug info region for this application */
        bzero(hotplug_info_ptr, sizeof(*hotplug_info_ptr));
    }

    return 0;
}