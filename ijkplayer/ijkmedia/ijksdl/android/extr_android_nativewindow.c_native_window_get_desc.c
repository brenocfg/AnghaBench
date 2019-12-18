#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int fcc_or_hal; } ;
typedef  TYPE_1__ AndroidHalFourccDescriptor ;

/* Variables and functions */
 int NELEM (TYPE_1__*) ; 
 TYPE_1__* g_hal_fcc_map ; 

AndroidHalFourccDescriptor *native_window_get_desc(int fourcc_or_hal)
{
    for (int i = 0; i < NELEM(g_hal_fcc_map); ++i) {
        AndroidHalFourccDescriptor *desc = &g_hal_fcc_map[i];
        if (desc->fcc_or_hal == fourcc_or_hal)
            return desc;
    }

    return NULL;
}