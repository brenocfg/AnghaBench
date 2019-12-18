#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned long arphys; unsigned long brphys; unsigned long atphys; unsigned long btphys; int num; int /*<<< orphan*/  port; int /*<<< orphan*/  mode; TYPE_1__* board; scalar_t__ btbuf; scalar_t__ atbuf; scalar_t__ brbuf; scalar_t__ arbuf; scalar_t__ overflow; } ;
typedef  TYPE_2__ cx_chan_t ;
struct TYPE_11__ {scalar_t__* tbuffer; scalar_t__* rbuffer; } ;
typedef  TYPE_3__ cx_buf_t ;
struct TYPE_9__ {scalar_t__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARBADRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARBADRU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARBCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARBSTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATBADRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATBADRU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRBADRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRBADRU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRBCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRBSTS (int /*<<< orphan*/ ) ; 
 int BSTS_OWN24 ; 
 int /*<<< orphan*/  BTBADRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTBADRU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAR (int /*<<< orphan*/ ) ; 
 int CCR_CLRCH ; 
 int CCR_ENRX ; 
 int CCR_ENTX ; 
 int CCR_INITCH ; 
 int /*<<< orphan*/  CMR (int /*<<< orphan*/ ) ; 
 int CMR_ASYNC ; 
 int CMR_HDLC ; 
 int CMR_RXDMA ; 
 int CMR_TXDMA ; 
 int /*<<< orphan*/  IER (int /*<<< orphan*/ ) ; 
 int IER_MDM ; 
 int IER_RET ; 
 int IER_RXD ; 
 int IER_TXD ; 
 int IER_TXMPTY ; 
 int /*<<< orphan*/  M_ASYNC ; 
 int /*<<< orphan*/  cx_cmd (int /*<<< orphan*/ ,int) ; 
 int cx_compute_buf_len (TYPE_2__*) ; 
 int /*<<< orphan*/  cx_set_dtr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_set_rts (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int) ; 

void cx_start_chan (cx_chan_t *c, cx_buf_t *cb, unsigned long phys)
{
	int command = 0;
	int mode = 0;
	int ier = 0;
	int rbsz;

	c->overflow = 0;

	/* Setting up buffers */
	if (cb) {
		c->arbuf = cb->rbuffer[0];
		c->brbuf = cb->rbuffer[1];
		c->atbuf = cb->tbuffer[0];
		c->btbuf = cb->tbuffer[1];
		c->arphys = phys + ((char*)c->arbuf - (char*)cb);
		c->brphys = phys + ((char*)c->brbuf - (char*)cb);
		c->atphys = phys + ((char*)c->atbuf - (char*)cb);
		c->btphys = phys + ((char*)c->btbuf - (char*)cb);
	}

	/* Set current channel number */
	outb (CAR(c->port), c->num & 3);

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

	/* rx */
	command |= CCR_ENRX;
	ier |= IER_RXD;
	if (c->board->dma) {
		mode |= CMR_RXDMA;
		if (c->mode == M_ASYNC)
			ier |= IER_RET;
	}

	/* tx */
	command |= CCR_ENTX;
	ier |= (c->mode == M_ASYNC) ? IER_TXD : (IER_TXD | IER_TXMPTY);
	if (c->board->dma)
		mode |= CMR_TXDMA;

	/* Set mode */
	outb (CMR(c->port), mode | (c->mode == M_ASYNC ? CMR_ASYNC : CMR_HDLC));

	/* Clear and initialize channel */
	cx_cmd (c->port, CCR_CLRCH);
	cx_cmd (c->port, CCR_INITCH | command);
	if (c->mode == M_ASYNC)
		cx_cmd (c->port, CCR_ENTX);

	/* Start receiver */
	rbsz = cx_compute_buf_len(c);
	outw (ARBCNT(c->port), rbsz);
	outw (BRBCNT(c->port), rbsz);
	outw (ARBSTS(c->port), BSTS_OWN24);
	outw (BRBSTS(c->port), BSTS_OWN24);

	if (c->mode == M_ASYNC)
		ier |= IER_MDM;

	/* Enable interrupts */
	outb (IER(c->port), ier);

	/* Clear DTR and RTS */
	cx_set_dtr (c, 0);
	cx_set_rts (c, 0);
}