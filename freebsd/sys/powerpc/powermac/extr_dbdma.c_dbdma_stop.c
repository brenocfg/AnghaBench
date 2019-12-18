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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  dbdma_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_CONTROL_REG ; 
 int /*<<< orphan*/  CHAN_STATUS_REG ; 
 int /*<<< orphan*/  DBDMA_REG_MASK_SHIFT ; 
 int DBDMA_STATUS_ACTIVE ; 
 int /*<<< orphan*/  DBDMA_STATUS_RUN ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int dbdma_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dbdma_stop(dbdma_channel_t *chan)
{
	uint32_t control_reg;

	control_reg = DBDMA_STATUS_RUN;
	control_reg <<= DBDMA_REG_MASK_SHIFT;

	dbdma_write_reg(chan, CHAN_CONTROL_REG, control_reg);

	while (dbdma_read_reg(chan, CHAN_STATUS_REG) & DBDMA_STATUS_ACTIVE)
		DELAY(5);
}