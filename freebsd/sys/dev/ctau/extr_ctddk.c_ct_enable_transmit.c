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
struct TYPE_6__ {int /*<<< orphan*/  DIR; } ;
struct TYPE_8__ {TYPE_2__* board; scalar_t__ num; int /*<<< orphan*/  CMD; TYPE_1__ TX; int /*<<< orphan*/ * tdphys; int /*<<< orphan*/ * tphys; scalar_t__ te; scalar_t__ tn; int /*<<< orphan*/  ST3; } ;
typedef  TYPE_3__ ct_chan_t ;
struct TYPE_7__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 unsigned char CMD_TX_DISABLE ; 
 unsigned char DIR_CHAIN_BOFE ; 
 unsigned char DIR_CHAIN_COFE ; 
 unsigned char DIR_CHAIN_EOME ; 
 int /*<<< orphan*/  DMABUFSZ ; 
 int /*<<< orphan*/  IER0 (int /*<<< orphan*/ ) ; 
 unsigned char IER0_TX_INTE_0 ; 
 unsigned char IER0_TX_INTE_1 ; 
 unsigned char IER0_TX_RDYE_0 ; 
 unsigned char IER0_TX_RDYE_1 ; 
 int /*<<< orphan*/  IER1 (int /*<<< orphan*/ ) ; 
 unsigned char IER1_TX_DMERE_0 ; 
 unsigned char IER1_TX_DMERE_1 ; 
 unsigned char IER1_TX_DME_0 ; 
 unsigned char IER1_TX_DME_1 ; 
 unsigned char ST3_TX_ENABLED ; 
 int /*<<< orphan*/  ct_start_transmitter (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,unsigned char) ; 

void ct_enable_transmit (ct_chan_t *c, int on)
{
	unsigned char st3, ier0, ier1;

	st3 = inb (c->ST3);
	/* enable or disable receiver */
	if (on && ! (st3 & ST3_TX_ENABLED)) {
		c->tn = 0;
		c->te = 0;
		ct_start_transmitter (c, 1 , c->tphys[0], DMABUFSZ,
			c->tdphys[0], c->tdphys[0]);
		outb (c->TX.DIR,
			DIR_CHAIN_EOME | DIR_CHAIN_BOFE | DIR_CHAIN_COFE);
	} else if (! on && (st3 & ST3_TX_ENABLED)) {
		outb (c->CMD, CMD_TX_DISABLE);

		ier0 = inb (IER0(c->board->port));
		ier0 &= c->num ? ~(IER0_TX_INTE_1 | IER0_TX_RDYE_1) :
			~(IER0_TX_INTE_0 | IER0_TX_RDYE_0);
		outb (IER0(c->board->port), ier0);

		ier1 = inb (IER1(c->board->port));
		ier1 &= c->num ? ~(IER1_TX_DMERE_1 | IER1_TX_DME_1) :
			~(IER1_TX_DMERE_0 | IER1_TX_DME_0);
		outb (IER1(c->board->port), ier1);
	}

}