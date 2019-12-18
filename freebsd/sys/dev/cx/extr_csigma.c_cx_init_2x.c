#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ port_t ;
struct TYPE_6__ {int num; long oscfreq; void* type; TYPE_2__* board; void* port; } ;
typedef  TYPE_1__ cx_chan_t ;
struct TYPE_8__ {scalar_t__ fast; } ;
struct TYPE_7__ {int num; int irq; int dma; scalar_t__ type; int bcr0; int nuniv; int /*<<< orphan*/  name; TYPE_1__* chan; scalar_t__ nasync; scalar_t__ nsync; scalar_t__ bcr1; TYPE_5__ opt; scalar_t__ port; } ;
typedef  TYPE_2__ cx_board_t ;

/* Variables and functions */
 int BCR02X_FAST ; 
 int BCR0_NORESET ; 
 int BSR2X_OSC_33 ; 
 scalar_t__ B_SIGMA_2X ; 
 int CRONYX_24 ; 
 void* CS0 (scalar_t__) ; 
 void* CS1 (scalar_t__) ; 
 int NCHAN ; 
 void* T_NONE ; 
 void* T_UNIV ; 
 TYPE_5__ board_opt_dflt ; 
 int /*<<< orphan*/  cx_reinit_board (TYPE_2__*) ; 
 int* dmamask ; 
 int* irqmask ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void cx_init_2x (cx_board_t *b, int num, port_t port, int irq, int dma,
	int rev, int osc)
{
	cx_chan_t *c;
	int i;

	/* Initialize board structure. */
	b->port = port;
	b->num = num;
	b->irq = irq;
	b->dma = dma;
	b->opt = board_opt_dflt;

	b->type = B_SIGMA_2X;

	/* Set channels 0 and 8 mode, set DMA and IRQ. */
	b->bcr0 = BCR0_NORESET | dmamask[b->dma] | irqmask[b->irq];
	if (b->type == B_SIGMA_2X && b->opt.fast)
		b->bcr0 |= BCR02X_FAST;

	/* Clear DTR[0..3] and DTR[8..12]. */
	b->bcr1 = 0;

	/* Initialize channel structures. */
	for (i=0; i<4; ++i) {
		b->chan[i+0].port  = CS0(port);
		b->chan[i+4].port  = CS1(port);
		b->chan[i+8].port  = CS0(port+0x10);
		b->chan[i+12].port = CS1(port+0x10);
	}
	for (c=b->chan; c<b->chan+NCHAN; ++c) {
		c->board = b;
		c->num = c - b->chan;
		c->type = T_NONE;
		c->oscfreq = (osc & BSR2X_OSC_33) ? 33000000L : 20000000L;
	}

	/* Check the board revision code. */
	strcpy (b->name, "22");
	b->chan[0].type = T_UNIV;
	b->chan[1].type = T_UNIV;
	b->nsync = b->nasync = 0;
	b->nuniv = 2;
	if (rev == CRONYX_24) {
		strcpy (b->name, "24");
		b->chan[2].type = T_UNIV;
		b->chan[3].type = T_UNIV;
		b->nuniv += 2;
	}
	strcat (b->name, (osc & BSR2X_OSC_33) ? "c" : "a");
	cx_reinit_board (b);
}