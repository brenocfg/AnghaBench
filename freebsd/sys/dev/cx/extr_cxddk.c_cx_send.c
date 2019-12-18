#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  port_t ;
struct TYPE_3__ {int num; unsigned char* atbuf; void** attach; unsigned char* btbuf; scalar_t__ mode; int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ cx_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATBCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATBSTS (int /*<<< orphan*/ ) ; 
 int BSTS_EOFR ; 
 int BSTS_INTR ; 
 int BSTS_OWN24 ; 
 int /*<<< orphan*/  BTBCNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTBSTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMABSTS (int /*<<< orphan*/ ) ; 
 int DMABSTS_NTBUF ; 
 int /*<<< orphan*/  IER (int /*<<< orphan*/ ) ; 
 int IER_RXD ; 
 int IER_TXD ; 
 int IER_TXMPTY ; 
 scalar_t__ M_ASYNC ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int cx_send (cx_chan_t *c, char *data, int len,
	void *attachment)
{
	unsigned char *buf;
	port_t cnt_port, sts_port;
	void **attp;

	/* Set the current channel number. */
	outb (CAR(c->port), c->num & 3);

	/* Determine the buffer order. */
	if (inb (DMABSTS(c->port)) & DMABSTS_NTBUF) {
		if (inb (BTBSTS(c->port)) & BSTS_OWN24) {
			buf	 = c->atbuf;
			cnt_port = ATBCNT(c->port);
			sts_port = ATBSTS(c->port);
			attp	 = &c->attach[0];
		} else {
			buf	 = c->btbuf;
			cnt_port = BTBCNT(c->port);
			sts_port = BTBSTS(c->port);
			attp	 = &c->attach[1];
		}
	} else {
		if (inb (ATBSTS(c->port)) & BSTS_OWN24) {
			buf	 = c->btbuf;
			cnt_port = BTBCNT(c->port);
			sts_port = BTBSTS(c->port);
			attp	 = &c->attach[1];
		} else {
			buf	 = c->atbuf;
			cnt_port = ATBCNT(c->port);
			sts_port = ATBSTS(c->port);
			attp	 = &c->attach[0];
		}
	}
	/* Is it busy? */
	if (inb (sts_port) & BSTS_OWN24)
		return -1;

	memcpy (buf, data, len);
	*attp = attachment;

	/* Start transmitter. */
	outw (cnt_port, len);
	outb (sts_port, BSTS_EOFR | BSTS_INTR | BSTS_OWN24);

	/* Enable TXMPTY interrupt,
	 * to catch the case when the second buffer is empty. */
	if (c->mode != M_ASYNC) {
		if ((inb(ATBSTS(c->port)) & BSTS_OWN24) &&
		    (inb(BTBSTS(c->port)) & BSTS_OWN24)) {
			outb (IER(c->port), IER_RXD | IER_TXD | IER_TXMPTY);
		} else
			outb (IER(c->port), IER_RXD | IER_TXD);
	}
	return 0;
}