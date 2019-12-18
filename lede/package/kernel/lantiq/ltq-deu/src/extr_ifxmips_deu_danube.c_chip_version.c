#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int* IFX_MPS_CHIPID ; 
 int ifx_danube_pre_1_4 ; 
 int /*<<< orphan*/  printk (char*) ; 

void chip_version(void) 
{

    /* DANUBE PRE 1.4 SOFTWARE FIX */
    int chip_id = 0;
    chip_id = *IFX_MPS_CHIPID;
    chip_id >>= 28;

    if (chip_id >= 4) {
        ifx_danube_pre_1_4 = 0;
        printk("Danube Chip ver. 1.4 detected. \n");
    }
    else {
        ifx_danube_pre_1_4 = 1; 
        printk("Danube Chip ver. 1.3 or below detected. \n");
    }

    return;
}