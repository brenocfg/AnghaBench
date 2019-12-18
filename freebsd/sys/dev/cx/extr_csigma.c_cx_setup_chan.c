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
struct TYPE_6__ {int num; scalar_t__ mode; int arphys; int brphys; int atphys; int btphys; scalar_t__ rts; scalar_t__ dtr; int /*<<< orphan*/  port; TYPE_1__* board; } ;
typedef  TYPE_2__ cx_chan_t ;
struct TYPE_5__ {int num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARBADRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARBADRU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATBADRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATBADRU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRBADRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRBADRU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTBADRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTBADRU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCR_CLRCH ; 
 int /*<<< orphan*/  LIVR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSVR_DTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSVR_RTS (int /*<<< orphan*/ ) ; 
 int MSV_TXCOUT ; 
 scalar_t__ M_ASYNC ; 
 int /*<<< orphan*/  cx_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_update_chan (TYPE_2__*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,unsigned short) ; 

void cx_setup_chan (cx_chan_t *c)
{
	/* set current channel number */
	outb (CAR(c->port), c->num & 3);

	/* reset the channel */
	cx_cmd (c->port, CCR_CLRCH);

	/* set LIVR to contain the board and channel numbers */
	outb (LIVR(c->port), c->board->num << 6 | c->num << 2);

	/* clear DTR, RTS, set TXCout/DTR pin */
	outb (MSVR_RTS(c->port), 0);
	outb (MSVR_DTR(c->port), c->mode==M_ASYNC ? 0 : MSV_TXCOUT);

	/* set receiver A buffer physical address */
	outw (ARBADRU(c->port), (unsigned short) (c->arphys>>16));
	outw (ARBADRL(c->port), (unsigned short) c->arphys);

	/* set receiver B buffer physical address */
	outw (BRBADRU(c->port), (unsigned short) (c->brphys>>16));
	outw (BRBADRL(c->port), (unsigned short) c->brphys);

	/* set transmitter A buffer physical address */
	outw (ATBADRU(c->port), (unsigned short) (c->atphys>>16));
	outw (ATBADRL(c->port), (unsigned short) c->atphys);

	/* set transmitter B buffer physical address */
	outw (BTBADRU(c->port), (unsigned short) (c->btphys>>16));
	outw (BTBADRL(c->port), (unsigned short) c->btphys);

	c->dtr = 0;
	c->rts = 0;

	cx_update_chan (c);
}