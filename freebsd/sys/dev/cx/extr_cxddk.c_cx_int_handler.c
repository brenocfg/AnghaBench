#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/  port; int /*<<< orphan*/  received_data; int /*<<< orphan*/  received_len; int /*<<< orphan*/  (* call_on_rx ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* call_on_msig ) (TYPE_1__*) ;int /*<<< orphan*/  mintr; } ;
typedef  TYPE_1__ cx_chan_t ;
struct TYPE_9__ {TYPE_1__* chan; int /*<<< orphan*/  port; } ;
typedef  TYPE_2__ cx_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  BRD_INTR_LEVEL ; 
 int /*<<< orphan*/  BSR (int /*<<< orphan*/ ) ; 
 int BSR_NOINTR ; 
 int /*<<< orphan*/  IACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  LIV_EXCEP 131 
#define  LIV_MODEM 130 
#define  LIV_RXDATA 129 
#define  LIV_TXDATA 128 
 int /*<<< orphan*/  MEOIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REOIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEOIR (int /*<<< orphan*/ ) ; 
 scalar_t__ T_NONE ; 
 int /*<<< orphan*/  cx_receive_interrupt (TYPE_1__*) ; 
 int /*<<< orphan*/  cx_transmit_interrupt (TYPE_1__*) ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx_int_handler (cx_board_t *b)
{
	unsigned char livr;
	cx_chan_t *c;

	while (! (inw (BSR(b->port)) & BSR_NOINTR)) {
		/* Enter the interrupt context, using IACK bus cycle.
		   Read the local interrupt vector register. */
		livr = inb (IACK(b->port, BRD_INTR_LEVEL));
		c = b->chan + (livr>>2 & 0xf);
		if (c->type == T_NONE)
			continue;
		switch (livr & 3) {
		case LIV_MODEM: 		/* modem interrupt */
			++c->mintr;
			if (c->call_on_msig)
				c->call_on_msig (c);
			outb (MEOIR(c->port), 0);
			break;
		case LIV_EXCEP: 		/* receive exception */
		case LIV_RXDATA:		/* receive interrupt */
			outb (REOIR(c->port), cx_receive_interrupt (c));
			if (c->call_on_rx && c->received_data) {
				c->call_on_rx (c, c->received_data,
					c->received_len);
				c->received_data = 0;
			}
			break;
		case LIV_TXDATA:		/* transmit interrupt */
			cx_transmit_interrupt (c);
			outb (TEOIR(c->port), 0);
			break;
		}
	}
}