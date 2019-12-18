#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mode; int obytes; int /*<<< orphan*/  port; int /*<<< orphan*/  opkts; int /*<<< orphan*/ * attach; int /*<<< orphan*/  (* call_on_tx ) (TYPE_1__*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  oerrs; int /*<<< orphan*/  (* call_on_err ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tintr; } ;
typedef  TYPE_1__ cx_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATBCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATBSTS (int /*<<< orphan*/ ) ; 
 unsigned char BSTS_OWN24 ; 
 int /*<<< orphan*/  BTBCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTBSTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CX_UNDERRUN ; 
 int /*<<< orphan*/  IER (int /*<<< orphan*/ ) ; 
 int IER_RXD ; 
 int IER_TXD ; 
 int IER_TXMPTY ; 
 scalar_t__ M_ASYNC ; 
 int /*<<< orphan*/  TISR (int /*<<< orphan*/ ) ; 
 unsigned char TIS_BB ; 
 unsigned char TIS_EOBUF ; 
 unsigned char TIS_TXDATA ; 
 unsigned char TIS_TXEMPTY ; 
 unsigned char TIS_UNDERRUN ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cx_transmit_interrupt (cx_chan_t *c)
{
	unsigned char tisr;
	int len = 0;

	++c->tintr;
	tisr = inb (TISR(c->port));
	if (tisr & TIS_UNDERRUN) {	/* Transmit underrun error */
		if (c->call_on_err)
			c->call_on_err (c, CX_UNDERRUN);
		++c->oerrs;
	} else if (tisr & (TIS_EOBUF | TIS_TXEMPTY | TIS_TXDATA)) {
		/* Call processing function */
		if (tisr & TIS_BB) {
			len = inw(BTBCNT(c->port));
			if (c->call_on_tx)
				c->call_on_tx (c, c->attach[1], len);
		} else {
			len = inw(ATBCNT(c->port));
			if (c->call_on_tx)
				c->call_on_tx (c, c->attach[0], len);
		}
		if (c->mode != M_ASYNC && len != 0)
			++c->opkts;
		c->obytes += len;
	}

	/* Enable TXMPTY interrupt,
	 * to catch the case when the second buffer is empty. */
	if (c->mode != M_ASYNC) {
		if ((inb (ATBSTS(c->port)) & BSTS_OWN24) &&
		   (inb (BTBSTS(c->port)) & BSTS_OWN24)) {
			outb (IER(c->port), IER_RXD | IER_TXD | IER_TXMPTY);
		} else
			outb (IER(c->port), IER_RXD | IER_TXD);
	}
}