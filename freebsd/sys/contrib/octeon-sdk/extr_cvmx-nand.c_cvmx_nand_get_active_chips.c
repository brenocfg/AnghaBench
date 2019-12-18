#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ page_size; } ;

/* Variables and functions */
 TYPE_1__* cvmx_nand_state ; 

int cvmx_nand_get_active_chips(void)
{
    int chip;
    int result = 0;
    for (chip=0; chip<8; chip++)
    {
        if (cvmx_nand_state[chip].page_size)
            result |= 1<<chip;
    }
    return result;
}