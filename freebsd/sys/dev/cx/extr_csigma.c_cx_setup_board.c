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
struct TYPE_6__ {int fast; } ;
struct TYPE_7__ {int dma; scalar_t__ type; int bcr0; int bcr0b; TYPE_3__* chan; TYPE_1__ opt; scalar_t__ port; int /*<<< orphan*/  bcr1b; int /*<<< orphan*/  bcr1; } ;
typedef  TYPE_2__ cx_board_t ;
typedef  int /*<<< orphan*/  cr_dat_tst_t ;
struct TYPE_8__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCR0 (scalar_t__) ; 
 int /*<<< orphan*/  BCR1 (scalar_t__) ; 
 int /*<<< orphan*/  BCR2 (scalar_t__) ; 
 int BCR2_BUS0 ; 
 int BCR2_BUS1 ; 
 int BCR2_TMS ; 
 scalar_t__ B_SIGMA_800 ; 
 int /*<<< orphan*/  DMA_MASK ; 
 int DMA_MASK_CLEAR ; 
 int /*<<< orphan*/  DMA_MODE ; 
 int DMA_MODE_MASTER ; 
 int NCHAN ; 
 scalar_t__ T_NONE ; 
 int /*<<< orphan*/  cx_download (scalar_t__,unsigned char const*,long,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cx_setup_chan (TYPE_3__*) ; 
 int /*<<< orphan*/  cx_setup_chip (TYPE_3__*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cx_setup_board (cx_board_t *b, const unsigned char *firmware,
	long bits, const cr_dat_tst_t *tst)
{
	int i;
#ifndef NDIS_MINIPORT_DRIVER
	/* Disable DMA channel. */
	outb (DMA_MASK, (b->dma & 3) | DMA_MASK_CLEAR);
#endif
	/* Reset the controller. */
	outb (BCR0(b->port), 0);
	if (b->chan[8].type || b->chan[12].type)
		outb (BCR0(b->port+0x10), 0);

	/* Load the firmware. */
	if (b->type == B_SIGMA_800) {
		/* Reset the controllers. */
		outb (BCR2(b->port), BCR2_TMS);
		if (b->chan[8].type || b->chan[12].type)
			outb (BCR2(b->port+0x10), BCR2_TMS);
		outb (BCR2(b->port), 0);
		if (b->chan[8].type || b->chan[12].type)
			outb (BCR2(b->port+0x10), 0);

		if (firmware &&
		    (! cx_download (b->port, firmware, bits, tst) ||
		    ((b->chan[8].type || b->chan[12].type) &&
		    ! cx_download (b->port+0x10, firmware, bits, tst))))
			return (0);
	}

	/*
	 * Set channels 0 and 8 to RS232 async. mode.
	 * Enable DMA and IRQ.
	 */
	outb (BCR0(b->port), b->bcr0);
	if (b->chan[8].type || b->chan[12].type)
		outb (BCR0(b->port+0x10), b->bcr0b);

	/* Clear DTR[0..3] and DTR[8..12]. */
	outw (BCR1(b->port), b->bcr1);
	if (b->chan[8].type || b->chan[12].type)
		outw (BCR1(b->port+0x10), b->bcr1b);

	if (b->type == B_SIGMA_800)
		outb (BCR2(b->port), b->opt.fast &
			(BCR2_BUS0 | BCR2_BUS1));

	/* Initialize all controllers. */
	for (i=0; i<NCHAN; i+=4)
		if (b->chan[i].type != T_NONE)
			cx_setup_chip (b->chan + i);
#ifndef NDIS_MINIPORT_DRIVER
	/* Set up DMA channel to master mode. */
	outb (DMA_MODE, (b->dma & 3) | DMA_MODE_MASTER);

	/* Enable DMA channel. */
	outb (DMA_MASK, b->dma & 3);
#endif
	/* Initialize all channels. */
	for (i=0; i<NCHAN; ++i)
		if (b->chan[i].type != T_NONE)
			cx_setup_chan (b->chan + i);
	return (1);
}