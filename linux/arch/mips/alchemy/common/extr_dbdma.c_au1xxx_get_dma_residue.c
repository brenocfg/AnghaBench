#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {TYPE_2__* chan_ptr; } ;
typedef  TYPE_1__ chan_tab_t ;
struct TYPE_4__ {scalar_t__ ddma_bytecnt; } ;
typedef  TYPE_2__ au1x_dma_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  wmb () ; 

u32 au1xxx_get_dma_residue(u32 chanid)
{
	chan_tab_t	*ctp;
	au1x_dma_chan_t *cp;
	u32		rv;

	ctp = *((chan_tab_t **)chanid);
	cp = ctp->chan_ptr;

	/* This is only valid if the channel is stopped. */
	rv = cp->ddma_bytecnt;
	wmb(); /* drain writebuffer */

	return rv;
}