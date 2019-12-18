#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {TYPE_3__* cur_ptr; int /*<<< orphan*/  chan_callparam; int /*<<< orphan*/  (* chan_callback ) (int,int /*<<< orphan*/ ) ;TYPE_2__* chan_ptr; } ;
typedef  TYPE_1__ chan_tab_t ;
struct TYPE_8__ {scalar_t__ ddma_irq; } ;
typedef  TYPE_2__ au1x_dma_chan_t ;
struct TYPE_9__ {int /*<<< orphan*/  dscr_nxtptr; } ;
typedef  TYPE_3__ au1x_ddma_desc_t ;
struct TYPE_10__ {size_t ddma_intstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSCR_GET_NXTPTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 size_t __ffs (size_t) ; 
 TYPE_1__** chan_tab_ptr ; 
 TYPE_5__* dbdma_gptr ; 
 TYPE_3__* phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static irqreturn_t dbdma_interrupt(int irq, void *dev_id)
{
	u32 intstat;
	u32 chan_index;
	chan_tab_t		*ctp;
	au1x_ddma_desc_t	*dp;
	au1x_dma_chan_t *cp;

	intstat = dbdma_gptr->ddma_intstat;
	wmb(); /* drain writebuffer */
	chan_index = __ffs(intstat);

	ctp = chan_tab_ptr[chan_index];
	cp = ctp->chan_ptr;
	dp = ctp->cur_ptr;

	/* Reset interrupt. */
	cp->ddma_irq = 0;
	wmb(); /* drain writebuffer */

	if (ctp->chan_callback)
		ctp->chan_callback(irq, ctp->chan_callparam);

	ctp->cur_ptr = phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));
	return IRQ_RETVAL(1);
}