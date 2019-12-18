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
 scalar_t__ JAZZ_R4030_CHNL_COUNT ; 
 int /*<<< orphan*/  printk (char*,int,unsigned int) ; 
 int /*<<< orphan*/  r4030_write_reg32 (scalar_t__,int) ; 
 scalar_t__ vdma_debug ; 

void vdma_set_count(int channel, int count)
{
	if (vdma_debug)
		printk("vdma_set_count: channel %d, count %08x\n", channel,
		       (unsigned) count);

	r4030_write_reg32(JAZZ_R4030_CHNL_COUNT + (channel << 5), count);
}