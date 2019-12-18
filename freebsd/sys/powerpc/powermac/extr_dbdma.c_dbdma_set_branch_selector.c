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
 int /*<<< orphan*/  CHAN_BRANCH_SELECT ; 
 int /*<<< orphan*/  DBDMA_REG_MASK_SHIFT ; 
 int /*<<< orphan*/  dbdma_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dbdma_set_branch_selector(dbdma_channel_t *chan, uint8_t mask, uint8_t val)
{
	uint32_t br_select;

	br_select = mask;
	br_select <<= DBDMA_REG_MASK_SHIFT;

	br_select |= val;
	dbdma_write_reg(chan, CHAN_BRANCH_SELECT, br_select);
}