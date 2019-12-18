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
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  dbdma_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_STATUS_REG ; 
 int dbdma_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

uint16_t
dbdma_get_chan_status(dbdma_channel_t *chan)
{
	uint32_t status_reg;

	status_reg = dbdma_read_reg(chan, CHAN_STATUS_REG);
	return (status_reg & 0x0000ffff);
}