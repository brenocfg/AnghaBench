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
typedef  scalar_t__ u_int32_t ;
struct aoa_dma {int bufsz; int slots; int blksz; int /*<<< orphan*/  channel; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  DBDMA_ALWAYS ; 
 int /*<<< orphan*/  DBDMA_COND_TRUE ; 
 int /*<<< orphan*/  DBDMA_NEVER ; 
 int /*<<< orphan*/  DBDMA_OUTPUT_MORE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  dbdma_insert_branch (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_insert_command (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbdma_insert_stop (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbdma_set_branch_selector (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dbdma_set_device_status (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbdma_sync_commands (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sndbuf_getbufaddr (int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aoa_dma_set_program(struct aoa_dma *dma)
{
	u_int32_t 		 addr;
	int 			 i;

	addr = (u_int32_t) sndbuf_getbufaddr(dma->buf);
	KASSERT(dma->bufsz == sndbuf_getsize(dma->buf), ("bad size"));

	dma->slots = dma->bufsz / dma->blksz;

	for (i = 0; i < dma->slots; ++i) {
		dbdma_insert_command(dma->channel, 
		    i, /* slot */
		    DBDMA_OUTPUT_MORE, /* command */
		    0, /* stream */
		    addr, /* data */
		    dma->blksz, /* count */
		    DBDMA_ALWAYS, /* interrupt */
		    DBDMA_COND_TRUE, /* branch */
		    DBDMA_NEVER, /* wait */
		    dma->slots + 1 /* branch_slot */
		);

		addr += dma->blksz;
	}

	/* Branch back to beginning. */
	dbdma_insert_branch(dma->channel, dma->slots, 0);

	/* STOP command to branch when S0 is asserted. */
	dbdma_insert_stop(dma->channel, dma->slots + 1);

	/* Set S0 as the condition to branch to STOP. */
	dbdma_set_branch_selector(dma->channel, 1 << 0, 1 << 0);
	dbdma_set_device_status(dma->channel, 1 << 0, 0);

	dbdma_sync_commands(dma->channel, BUS_DMASYNC_PREWRITE);
}