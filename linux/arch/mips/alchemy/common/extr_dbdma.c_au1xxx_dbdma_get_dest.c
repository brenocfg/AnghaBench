#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {TYPE_2__* get_ptr; } ;
typedef  TYPE_1__ chan_tab_t ;
struct TYPE_5__ {int dscr_cmd0; int dscr_cmd1; int /*<<< orphan*/  dscr_nxtptr; scalar_t__ dscr_stat; int /*<<< orphan*/  dscr_dest0; } ;
typedef  TYPE_2__ au1x_ddma_desc_t ;

/* Variables and functions */
 int DSCR_CMD0_V ; 
 int /*<<< orphan*/  DSCR_GET_NXTPTR (int /*<<< orphan*/ ) ; 
 TYPE_2__* phys_to_virt (int /*<<< orphan*/ ) ; 

u32 au1xxx_dbdma_get_dest(u32 chanid, void **buf, int *nbytes)
{
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;
	u32			rv;

	/*
	 * I guess we could check this to be within the
	 * range of the table......
	 */
	ctp = *((chan_tab_t **)chanid);

	/*
	 * We should have multiple callers for a particular channel,
	 * an interrupt doesn't affect this pointer nor the descriptor,
	 * so no locking should be needed.
	 */
	dp = ctp->get_ptr;

	/*
	 * If the descriptor is valid, we are way ahead of the DMA
	 * engine, so just return an error condition.
	 */
	if (dp->dscr_cmd0 & DSCR_CMD0_V)
		return 0;

	/* Return buffer address and byte count. */
	*buf = (void *)(phys_to_virt(dp->dscr_dest0));
	*nbytes = dp->dscr_cmd1;
	rv = dp->dscr_stat;

	/* Get next descriptor pointer. */
	ctp->get_ptr = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));

	/* Return something non-zero. */
	return rv;
}