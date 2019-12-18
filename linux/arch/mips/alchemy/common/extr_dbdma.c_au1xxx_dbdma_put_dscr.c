#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_7__ {TYPE_3__* put_ptr; TYPE_1__* chan_ptr; } ;
typedef  TYPE_2__ chan_tab_t ;
struct TYPE_8__ {int dscr_cmd0; int /*<<< orphan*/  dscr_nxtptr; scalar_t__ dscr_cmd1; int /*<<< orphan*/  dscr_source1; int /*<<< orphan*/  dscr_dest1; int /*<<< orphan*/  dscr_source0; int /*<<< orphan*/  dscr_dest0; } ;
typedef  TYPE_3__ au1x_ddma_desc_t ;
struct TYPE_6__ {scalar_t__ ddma_dbell; } ;

/* Variables and functions */
 int DSCR_CMD0_IE ; 
 int DSCR_CMD0_V ; 
 int /*<<< orphan*/  DSCR_GET_NXTPTR (int /*<<< orphan*/ ) ; 
 TYPE_3__* phys_to_virt (int /*<<< orphan*/ ) ; 

u32 au1xxx_dbdma_put_dscr(u32 chanid, au1x_ddma_desc_t *dscr)
{
	chan_tab_t *ctp;
	au1x_ddma_desc_t *dp;
	u32 nbytes = 0;

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
	dp = ctp->put_ptr;

	/*
	 * If the descriptor is valid, we are way ahead of the DMA
	 * engine, so just return an error condition.
	 */
	if (dp->dscr_cmd0 & DSCR_CMD0_V)
		return 0;

	/* Load up buffer addresses and byte count. */
	dp->dscr_dest0 = dscr->dscr_dest0;
	dp->dscr_source0 = dscr->dscr_source0;
	dp->dscr_dest1 = dscr->dscr_dest1;
	dp->dscr_source1 = dscr->dscr_source1;
	dp->dscr_cmd1 = dscr->dscr_cmd1;
	nbytes = dscr->dscr_cmd1;
	/* Allow the caller to specify if an interrupt is generated */
	dp->dscr_cmd0 &= ~DSCR_CMD0_IE;
	dp->dscr_cmd0 |= dscr->dscr_cmd0 | DSCR_CMD0_V;
	ctp->chan_ptr->ddma_dbell = 0;

	/* Get next descriptor pointer. */
	ctp->put_ptr = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));

	/* Return something non-zero. */
	return nbytes;
}