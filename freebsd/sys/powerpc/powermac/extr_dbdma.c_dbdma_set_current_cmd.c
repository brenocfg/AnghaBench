#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct dbdma_command {int dummy; } ;
struct TYPE_4__ {scalar_t__ sc_slots_pa; } ;
typedef  TYPE_1__ dbdma_channel_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_CMDPTR ; 
 int /*<<< orphan*/  dbdma_write_reg (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

void
dbdma_set_current_cmd(dbdma_channel_t *chan, int slot)
{
	uint32_t cmd;

	cmd = chan->sc_slots_pa + slot * sizeof(struct dbdma_command);
	dbdma_write_reg(chan, CHAN_CMDPTR, cmd);
}