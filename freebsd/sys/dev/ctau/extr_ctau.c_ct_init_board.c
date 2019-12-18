#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  port_t ;
struct TYPE_5__ {int type; int num; int irq; int dma; long osc; int bcr0; scalar_t__ e1cfg; scalar_t__ bcr1; int /*<<< orphan*/  name; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ ct_board_t ;

/* Variables and functions */
 int BCR0_HDRUN ; 
 int B_TAU ; 
 int B_TAU2 ; 
 int B_TAU2_E1 ; 
 int B_TAU2_E1D ; 
 int B_TAU2_G703 ; 
 int B_TAU_E1 ; 
 int B_TAU_E1C ; 
 int B_TAU_E1D ; 
 int B_TAU_G703 ; 
 int B_TAU_G703C ; 
 int NCHAN ; 
 int /*<<< orphan*/  ct_init_chan (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ct_reinit_board (TYPE_1__*) ; 
 int* dmamask ; 
 int* irqmask ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void ct_init_board (ct_board_t *b, int num, port_t port, int irq, int dma,
	int type, long osc)
{
	int i;

	/* Initialize board structure. */
	b->type = type;
	b->port = port;
	b->num = num;
	b->irq = irq;
	b->dma = dma;
	b->osc = osc;

	/* Get the board type. */
	if (b->type == B_TAU)		 strcpy (b->name, "Tau");
	else if (b->type == B_TAU_E1)	 strcpy (b->name, "Tau/E1");
	else if (b->type == B_TAU_E1C)	 strcpy (b->name, "Tau/E1c");
	else if (b->type == B_TAU_E1D)	 strcpy (b->name, "Tau/E1d");
	else if (b->type == B_TAU_G703)  strcpy (b->name, "Tau/G.703");
	else if (b->type == B_TAU_G703C) strcpy (b->name, "Tau/G.703c");
	else if (b->type == B_TAU2)	 strcpy (b->name, "Tau2");
	else if (b->type == B_TAU2_E1)	 strcpy (b->name, "Tau2/E1");
	else if (b->type == B_TAU2_E1D)  strcpy (b->name, "Tau2/E1d");
	else if (b->type == B_TAU2_G703) strcpy (b->name, "Tau2/G.703");
	else				 strcpy (b->name, "Tau/???");

	/* Set DMA and IRQ. */
	b->bcr0 = BCR0_HDRUN | dmamask[b->dma] | irqmask[b->irq];

	/* Clear DTR[0..1]. */
	b->bcr1 = 0;
	b->e1cfg = 0;

	/* Initialize channel structures. */
	for (i=0; i<NCHAN; ++i)
		ct_init_chan (b, i);
	ct_reinit_board (b);
}