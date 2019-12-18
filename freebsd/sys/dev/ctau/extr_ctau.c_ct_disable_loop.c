#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  loop; } ;
struct TYPE_10__ {TYPE_2__ md2; } ;
struct TYPE_11__ {scalar_t__ mode; int lx; TYPE_3__ opt; int /*<<< orphan*/  MD2; TYPE_1__* board; int /*<<< orphan*/  TXS; int /*<<< orphan*/  RXS; scalar_t__ num; } ;
typedef  TYPE_4__ ct_chan_t ;
struct TYPE_8__ {int bcr1; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCR1 (int /*<<< orphan*/ ) ; 
 int BCR1_TXCOUT0 ; 
 int BCR1_TXCOUT1 ; 
 int CCR2_LLOOP ; 
 unsigned char CLK_INT ; 
 unsigned char CLK_LINE ; 
 unsigned char CLK_MASK ; 
 int /*<<< orphan*/  DS_CCR2 ; 
 int /*<<< orphan*/  DS_LICR ; 
 unsigned short E1CS0 (int /*<<< orphan*/ ) ; 
 unsigned short E1CS1 (int /*<<< orphan*/ ) ; 
 int LICR_JA_TX ; 
 int /*<<< orphan*/  LX_CCR1 ; 
 int LX_HDB3 ; 
 int LX_LOS ; 
 int /*<<< orphan*/  MD2_FDX ; 
 scalar_t__ M_E1 ; 
 scalar_t__ M_G703 ; 
 scalar_t__ M_HDLC ; 
 scalar_t__ ct_get_baud (TYPE_4__*) ; 
 int cte_in (unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cte_out (unsigned short,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctg_outx (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void ct_disable_loop (ct_chan_t *c)
{
	if (c->mode == M_E1) {
		unsigned short p = c->num ? E1CS1 (c->board->port) :
					    E1CS0 (c->board->port);

		/* Local loopback. */
		cte_out (p, DS_CCR2, cte_in (p, DS_CCR2) & ~CCR2_LLOOP);

		/* Disable jitter attenuator at the transmit side. */
		cte_out (p, DS_LICR, cte_in (p, DS_LICR) & ~LICR_JA_TX);
		return;
	} else if (c->mode == M_G703) {
		c->lx = LX_LOS | LX_HDB3;
		ctg_outx (c, LX_CCR1, c->lx);
		return;
	} else if (c->mode == M_HDLC && ct_get_baud(c)) {
		unsigned char rxs = inb (c->RXS) & ~CLK_MASK;
		unsigned char txs = inb (c->TXS) & ~CLK_MASK;
		int txcout = c->num ? BCR1_TXCOUT1 : BCR1_TXCOUT0;
		c->opt.md2.loop = MD2_FDX;

		outb (BCR1(c->board->port), c->board->bcr1 & ~txcout);

		outb (c->RXS, rxs | CLK_LINE);
		if (ct_get_baud (c))
			outb (c->TXS, txs | CLK_INT);
		else
			outb (c->TXS, txs | CLK_LINE);

		c->board->bcr1 |= txcout;
		outb (BCR1(c->board->port), c->board->bcr1);

		outb (c->MD2, *(unsigned char*)&c->opt.md2);
		return;
	}
}