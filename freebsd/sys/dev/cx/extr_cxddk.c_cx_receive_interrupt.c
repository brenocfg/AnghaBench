#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  port_t ;
struct TYPE_13__ {scalar_t__ ixon; } ;
struct TYPE_14__ {TYPE_1__ cor2; } ;
struct TYPE_15__ {scalar_t__ mode; unsigned long brphys; unsigned char* brbuf; unsigned long arphys; unsigned char* arbuf; int ibytes; unsigned char* received_data; int received_len; int overflow; TYPE_2__ aopt; int /*<<< orphan*/  port; int /*<<< orphan*/  ipkts; int /*<<< orphan*/  ierrs; int /*<<< orphan*/  (* call_on_err ) (TYPE_3__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  rintr; } ;
typedef  TYPE_3__ cx_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARBCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARBSTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRBCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BRBSTS (int /*<<< orphan*/ ) ; 
 int BSTS_OWN24 ; 
 int /*<<< orphan*/  CX_BREAK ; 
 int /*<<< orphan*/  CX_CRC ; 
 int /*<<< orphan*/  CX_FRAME ; 
 int /*<<< orphan*/  CX_OVERFLOW ; 
 int /*<<< orphan*/  CX_OVERRUN ; 
 unsigned long DMABUFSZ ; 
 scalar_t__ M_ASYNC ; 
 int /*<<< orphan*/  RCBADRL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCBADRU (int /*<<< orphan*/ ) ; 
 int REOI_DISCEXC ; 
 int REOI_TERMBUFF ; 
 unsigned short RISA_BREAK ; 
 unsigned short RISA_FRERR ; 
 unsigned short RISA_PARERR ; 
 unsigned short RISA_SCMASK ; 
 unsigned short RISA_TIMEOUT ; 
 unsigned short RISH_CRCERR ; 
 unsigned short RISH_RESIND ; 
 unsigned short RISH_RXABORT ; 
 int /*<<< orphan*/  RISR (int /*<<< orphan*/ ) ; 
 unsigned short RIS_BB ; 
 unsigned short RIS_EOBUF ; 
 unsigned short RIS_EOFR ; 
 unsigned short RIS_OVERRUN ; 
 int cx_compute_buf_len (TYPE_3__*) ; 
 int inb (int /*<<< orphan*/ ) ; 
 void* inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx_receive_interrupt (cx_chan_t *c)
{
	unsigned short risr;
	int len = 0, rbsz;

	++c->rintr;
	risr = inw (RISR(c->port));

	/* Compute optimal receiver buffer length */
	rbsz = cx_compute_buf_len(c);
	if (c->mode == M_ASYNC && (risr & RISA_TIMEOUT)) {
		unsigned long rcbadr = (unsigned short) inw (RCBADRL(c->port)) |
			(long) inw (RCBADRU(c->port)) << 16;
		unsigned char *buf = NULL;
		port_t cnt_port = 0, sts_port = 0;

		if (rcbadr >= c->brphys && rcbadr < c->brphys+DMABUFSZ) {
			buf = c->brbuf;
			len = rcbadr - c->brphys;
			cnt_port = BRBCNT(c->port);
			sts_port = BRBSTS(c->port);
		} else if (rcbadr >= c->arphys && rcbadr < c->arphys+DMABUFSZ) {
			buf = c->arbuf;
			len = rcbadr - c->arphys;
			cnt_port = ARBCNT(c->port);
			sts_port = ARBSTS(c->port);
		}

		if (len) {
			c->ibytes += len;
			c->received_data = buf;
			c->received_len = len;

			/* Restart receiver. */
			outw (cnt_port, rbsz);
			outb (sts_port, BSTS_OWN24);
		}
		return (REOI_TERMBUFF);
	}

	/* Receive errors. */
	if (risr & RIS_OVERRUN) {
		++c->ierrs;
		if (c->call_on_err)
			c->call_on_err (c, CX_OVERRUN);
	} else if (c->mode != M_ASYNC && (risr & RISH_CRCERR)) {
		++c->ierrs;
		if (c->call_on_err)
			c->call_on_err (c, CX_CRC);
	} else if (c->mode != M_ASYNC && (risr & (RISH_RXABORT | RISH_RESIND))) {
		++c->ierrs;
		if (c->call_on_err)
			c->call_on_err (c, CX_FRAME);
	} else if (c->mode == M_ASYNC && (risr & RISA_PARERR)) {
		++c->ierrs;
		if (c->call_on_err)
			c->call_on_err (c, CX_CRC);
	} else if (c->mode == M_ASYNC && (risr & RISA_FRERR)) {
		++c->ierrs;
		if (c->call_on_err)
			c->call_on_err (c, CX_FRAME);
	} else if (c->mode == M_ASYNC && (risr & RISA_BREAK)) {
		if (c->call_on_err)
			c->call_on_err (c, CX_BREAK);
	} else if (! (risr & RIS_EOBUF)) {
		++c->ierrs;
	} else {
		/* Handle received data. */
		len = (risr & RIS_BB) ? inw(BRBCNT(c->port)) : inw(ARBCNT(c->port));

		if (len > DMABUFSZ) {
			/* Fatal error: actual DMA transfer size
			 * exceeds our buffer size.  It could be caused
			 * by incorrectly programmed DMA register or
			 * hardware fault.  Possibly, should panic here. */
			len = DMABUFSZ;
		} else if (c->mode != M_ASYNC && ! (risr & RIS_EOFR)) {
			/* The received frame does not fit in the DMA buffer.
			 * It could be caused by serial lie noise,
			 * or if the peer has too big MTU. */
			if (! c->overflow) {
				if (c->call_on_err)
					c->call_on_err (c, CX_OVERFLOW);
				c->overflow = 1;
				++c->ierrs;
			}
		} else if (! c->overflow) {
			if (risr & RIS_BB) {
				c->received_data = c->brbuf;
				c->received_len = len;
			} else {
				c->received_data = c->arbuf;
				c->received_len = len;
			}
			if (c->mode != M_ASYNC)
				++c->ipkts;
			c->ibytes += len;
		} else
			c->overflow = 0;
	}

	/* Restart receiver. */
	if (! (inb (ARBSTS(c->port)) & BSTS_OWN24)) {
		outw (ARBCNT(c->port), rbsz);
		outb (ARBSTS(c->port), BSTS_OWN24);
	}
	if (! (inb (BRBSTS(c->port)) & BSTS_OWN24)) {
		outw (BRBCNT(c->port), rbsz);
		outb (BRBSTS(c->port), BSTS_OWN24);
	}

	/* Discard exception characters. */
	if ((risr & RISA_SCMASK) && c->aopt.cor2.ixon)
		return (REOI_DISCEXC);
	else
		return (0);
}