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
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ cx_board_t ;

/* Variables and functions */
 int BCR0 (int /*<<< orphan*/ ) ; 
 int BCR0_NORESET ; 
 int BSR (int /*<<< orphan*/ ) ; 
 int BSR_VAR_MASK ; 
 int CAR (int /*<<< orphan*/ ) ; 
 int CCR_CLRCH ; 
 int CCR_ENTX ; 
 int CCR_INITCH ; 
 int CMR (int /*<<< orphan*/ ) ; 
 int CMR_HDLC ; 
 int CRONYX_400 ; 
 int /*<<< orphan*/  CS0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS1 (int /*<<< orphan*/ ) ; 
 int IER (int /*<<< orphan*/ ) ; 
 int IER_TXMPTY ; 
 int TBPR (int /*<<< orphan*/ ) ; 
 int TCOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_cmd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_reset (int /*<<< orphan*/ ) ; 
 int inb (int) ; 
 int* irqmask ; 
 int /*<<< orphan*/  outb (int,int) ; 

int cx_probe_irq (cx_board_t *b, int irq)
{
	int mask, rev;
        port_t port;

	rev = inb (BSR(b->port));
        port = ((rev & BSR_VAR_MASK) != CRONYX_400) ? CS0(b->port) : CS1(b->port);

	outb (0x20, 0x0a);
	mask = inb (0x20);
	outb (0xa0, 0x0a);
	mask |= inb (0xa0) << 8;

	if (irq > 0) {
		outb (BCR0(b->port), BCR0_NORESET | irqmask[irq]);
		outb (CAR(port), 0);
		cx_cmd (port, CCR_CLRCH);
		outb (CMR(port), CMR_HDLC);
		outb (TCOR(port), 0);
		outb (TBPR(port), 1);
		cx_cmd (port, CCR_INITCH | CCR_ENTX);
		outb (IER(port), IER_TXMPTY);
	} else if (irq < 0) {
		cx_reset (port);
		if (-irq > 7) {
			outb (0xa0, 0x60 | ((-irq) & 7));
			outb (0x20, 0x62);
		} else
			outb (0x20, 0x60 | (-irq));
	} else
		outb (BCR0(b->port), 0);
	return mask;
}