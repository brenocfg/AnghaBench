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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int ioread32be (int*) ; 
 int /*<<< orphan*/  iowrite32be (int,int*) ; 

void fman_set_congestion_group_pfc_priority(uint32_t *cpg_rg,
                                            uint32_t congestion_group_id,
                                            uint8_t priority_bit_map,
                                            uint32_t reg_num)
{
	uint32_t offset, tmp = 0;

    offset  = (congestion_group_id%4)*8;

    tmp = ioread32be(&cpg_rg[reg_num]);
    tmp &= ~(0xFF<<offset);
    tmp |= (uint32_t)priority_bit_map << offset;

    iowrite32be(tmp,&cpg_rg[reg_num]);
}