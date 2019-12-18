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
struct TYPE_3__ {unsigned long long coremask; } ;
typedef  TYPE_1__ cvmx_app_hotplug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CIU_MBOX_SETX (int) ; 
 int CVMX_MAX_CORES ; 
 TYPE_1__* cvmx_app_hotplug_get_info_at_index (int) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int cvmx_app_hotplug_call_add_cores_callback(int index)
{
    cvmx_app_hotplug_info_t *ai;
    int i;
    if (!(ai = cvmx_app_hotplug_get_info_at_index(index)))
    {
        printf("\nERROR: Failed to get hotplug info for app at index=%d\n", index);
        return -1;
    }
   /* Send IPIs to all application cores to request add_cores callback*/
    for (i=0; i<CVMX_MAX_CORES; i++) {
            if (ai->coremask & (1ull<<i))
                cvmx_write_csr(CVMX_CIU_MBOX_SETX(i), 4);
    }
    return 0;
}