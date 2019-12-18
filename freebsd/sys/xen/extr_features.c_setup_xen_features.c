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
struct TYPE_3__ {int submap_idx; int submap; } ;
typedef  TYPE_1__ xen_feature_info_t ;

/* Variables and functions */
 scalar_t__ HYPERVISOR_xen_version (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int XENFEAT_NR_SUBMAPS ; 
 int /*<<< orphan*/  XENVER_get_features ; 
 int* xen_features ; 

void
setup_xen_features(void)
{
        xen_feature_info_t fi;
        int i, j;

        for (i = 0; i < XENFEAT_NR_SUBMAPS; i++) {
                fi.submap_idx = i;
                if (HYPERVISOR_xen_version(XENVER_get_features, &fi) < 0)
                        break;
                for (j = 0; j < 32; j++)
                        xen_features[i*32 + j] = !!(fi.submap & 1<<j);
        }
}