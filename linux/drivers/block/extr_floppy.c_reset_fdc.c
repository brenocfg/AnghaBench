#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ version; int dtr; int dor; scalar_t__ reset; } ;

/* Variables and functions */
 TYPE_1__* FDCS ; 
 scalar_t__ FDC_82072A ; 
 int /*<<< orphan*/  FD_DOR ; 
 int /*<<< orphan*/  FD_RESET_DELAY ; 
 int /*<<< orphan*/  FD_STATUS ; 
 unsigned long claim_dma_lock () ; 
 int /*<<< orphan*/  do_floppy ; 
 int /*<<< orphan*/  fd_disable_dma () ; 
 int /*<<< orphan*/  fd_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_dma_lock (unsigned long) ; 
 int /*<<< orphan*/  reset_fdc_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_interrupt ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_fdc(void)
{
	unsigned long flags;

	do_floppy = reset_interrupt;
	FDCS->reset = 0;
	reset_fdc_info(0);

	/* Pseudo-DMA may intercept 'reset finished' interrupt.  */
	/* Irrelevant for systems with true DMA (i386).          */

	flags = claim_dma_lock();
	fd_disable_dma();
	release_dma_lock(flags);

	if (FDCS->version >= FDC_82072A)
		fd_outb(0x80 | (FDCS->dtr & 3), FD_STATUS);
	else {
		fd_outb(FDCS->dor & ~0x04, FD_DOR);
		udelay(FD_RESET_DELAY);
		fd_outb(FDCS->dor, FD_DOR);
	}
}