#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ port_t ;
struct TYPE_5__ {int num; long oscfreq; int type; TYPE_2__* board; void* port; } ;
typedef  TYPE_1__ cx_chan_t ;
struct TYPE_6__ {int num; int irq; int dma; int bcr0; int bcr0b; scalar_t__ nsync; scalar_t__ nuniv; scalar_t__ nasync; TYPE_1__* chan; int /*<<< orphan*/  name; scalar_t__ bcr1b; scalar_t__ bcr1; int /*<<< orphan*/  type; int /*<<< orphan*/  opt; scalar_t__ port; } ;
typedef  TYPE_2__ cx_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_SIGMA_800 ; 
 void* CS0 (scalar_t__) ; 
 void* CS1 (scalar_t__) ; 
 void* CS1A (scalar_t__) ; 
 int NCHAN ; 
#define  T_ASYNC 135 
 int T_NONE ; 
#define  T_SYNC_RS232 134 
#define  T_SYNC_RS449 133 
#define  T_SYNC_V35 132 
#define  T_UNIV 131 
#define  T_UNIV_RS232 130 
#define  T_UNIV_RS449 129 
#define  T_UNIV_V35 128 
 int /*<<< orphan*/  board_opt_dflt ; 
 scalar_t__ cx_probe_chip (void*) ; 
 int /*<<< orphan*/  cx_reinit_board (TYPE_2__*) ; 
 int* dmamask ; 
 int* irqmask ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void cx_init_800 (cx_board_t *b, int num, port_t port, int irq, int dma,
	int chain)
{
	cx_chan_t *c;
	int i;

	/* Initialize board structure. */
	b->port = port;
	b->num = num;
	b->irq = irq;
	b->dma = dma;
	b->opt = board_opt_dflt;
	b->type = B_SIGMA_800;

	/* Set channels 0 and 8 mode, set DMA and IRQ. */
	b->bcr0 = b->bcr0b = dmamask[b->dma] | irqmask[b->irq];

	/* Clear DTR[0..7] and DTR[8..15]. */
	b->bcr1 = b->bcr1b = 0;

	strcpy (b->name, "800");
	if (chain)
		strcat (b->name, "/800");

	/* Initialize channel structures. */
	for (i=0; i<4; ++i) {
		b->chan[i+0].port  = CS0(port);
		b->chan[i+4].port  = cx_probe_chip (CS1A(port)) ?
			CS1A(port) : CS1(port);
		b->chan[i+8].port  = CS0(port+0x10);
		b->chan[i+12].port = CS1(port+0x10);
	}
	for (c=b->chan; c<b->chan+NCHAN; ++c) {
		c->board = b;
		c->num = c - b->chan;
		c->oscfreq = 33000000L;
		c->type = (c->num < 8 || chain) ? T_UNIV_RS232 : T_NONE;
	}

	b->nuniv = b->nsync = b->nasync = 0;
	for (c=b->chan; c<b->chan+NCHAN; ++c)
		switch (c->type) {
		case T_ASYNC:      ++b->nasync; break;
		case T_UNIV:
		case T_UNIV_RS232:
		case T_UNIV_RS449:
		case T_UNIV_V35:   ++b->nuniv;  break;
		case T_SYNC_RS232:
		case T_SYNC_V35:
		case T_SYNC_RS449: ++b->nsync;  break;
		}

	cx_reinit_board (b);
}