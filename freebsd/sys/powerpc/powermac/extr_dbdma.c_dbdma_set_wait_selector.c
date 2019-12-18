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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dbdma_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_WAIT_SELECT ; 
 int /*<<< orphan*/  DBDMA_REG_MASK_SHIFT ; 
 int /*<<< orphan*/  dbdma_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dbdma_set_wait_selector(dbdma_channel_t *chan, uint8_t mask, uint8_t val)
{
	uint32_t wait_select;

	wait_select = mask;
	wait_select <<= DBDMA_REG_MASK_SHIFT;
	wait_select |= val;
	dbdma_write_reg(chan, CHAN_WAIT_SELECT, wait_select);
}