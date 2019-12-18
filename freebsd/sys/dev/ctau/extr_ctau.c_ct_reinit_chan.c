#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* encod; } ;
struct TYPE_12__ {TYPE_3__ md2; } ;
struct TYPE_10__ {int rate; int /*<<< orphan*/  cas; } ;
struct TYPE_9__ {scalar_t__ txs; } ;
struct TYPE_14__ {scalar_t__ mode; int baud; int type; int /*<<< orphan*/  num; TYPE_7__* board; TYPE_4__ opt; TYPE_2__ gopt; TYPE_1__ hopt; } ;
typedef  TYPE_6__ ct_chan_t ;
struct TYPE_13__ {long s1; long s0; int bcr2; int /*<<< orphan*/  cfg; } ;
struct TYPE_15__ {TYPE_5__ opt; } ;
typedef  TYPE_7__ ct_board_t ;

/* Variables and functions */
 int BCR2_INVRXC0 ; 
 int BCR2_INVRXC1 ; 
 int BCR2_INVTXC0 ; 
 int BCR2_INVTXC1 ; 
 int /*<<< orphan*/  CFG_B ; 
 int /*<<< orphan*/  CFG_C ; 
 scalar_t__ CLK_LINE ; 
 void* MD2_ENCOD_NRZ ; 
 void* MD2_ENCOD_NRZI ; 
 scalar_t__ M_ASYNC ; 
 scalar_t__ M_E1 ; 
 scalar_t__ M_G703 ; 
 scalar_t__ M_HDLC ; 
#define  T_E1 131 
#define  T_E1_SERIAL 130 
#define  T_G703 129 
#define  T_G703_SERIAL 128 

void ct_reinit_chan (ct_chan_t *c)
{
	ct_board_t *b = c->board;
	long s;
	int i;

	if (c->hopt.txs == CLK_LINE) {
		/* External clock mode -- set zero baud rate. */
		if (c->mode != M_ASYNC)
			c->baud = 0;
	} else if (c->baud == 0) {
		/* No baud rate in internal clock mode -- set default values. */
		if (c->mode == M_ASYNC)
			c->baud = 9600;
		else if (c->mode == M_HDLC)
			c->baud = 64000;
	}
	switch (c->type) {
	case T_E1_SERIAL:
		if (b->opt.cfg == CFG_B)
			break;
		/* Fall through... */
	case T_E1:
		c->mode = M_E1;
		c->hopt.txs = CLK_LINE;

		/* Compute the baud value. */
		if (c->num) {
			s = b->opt.s1;
			if (b->opt.cfg == CFG_C)
				s &=~ b->opt.s0;
		} else
			s = b->opt.s0;
		/* Skip timeslot 16 in CAS mode. */
		if (c->gopt.cas)
			s &=~ (1L << 16);

		c->baud = 0;
		for (i=0; i<32; ++i)
			if ((s >> i) & 1)
				c->baud += 64000;
		c->gopt.rate = c->baud / 1000;

		/* Set NRZ and clear INVCLK. */
		c->opt.md2.encod = MD2_ENCOD_NRZ;
		c->board->opt.bcr2 &= c->num ?
			~(BCR2_INVTXC1 | BCR2_INVRXC1) :
			~(BCR2_INVTXC0 | BCR2_INVRXC0);
		break;

	case T_G703_SERIAL:
		if (b->opt.cfg == CFG_B)
			break;
		/* Fall through... */
	case T_G703:
		c->mode = M_G703;
		c->hopt.txs = CLK_LINE;
		c->baud = c->gopt.rate * 1000L;

		/* Set NRZ/NRZI and clear INVCLK. */
		if (c->opt.md2.encod != MD2_ENCOD_NRZ &&
		    c->opt.md2.encod != MD2_ENCOD_NRZI)
			c->opt.md2.encod = MD2_ENCOD_NRZ;
		c->board->opt.bcr2 &= c->num ?
			~(BCR2_INVTXC1 | BCR2_INVRXC1) :
			~(BCR2_INVTXC0 | BCR2_INVRXC0);
		break;
	}
}