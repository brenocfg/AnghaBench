#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int port_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCR0 (int) ; 
 int /*<<< orphan*/  BCR0_NORESET ; 
 int /*<<< orphan*/  BSR (int) ; 
 int BSR_NOCHAIN ; 
 int /*<<< orphan*/  CS0 (int) ; 
 int /*<<< orphan*/  CS1 (int) ; 
 int /*<<< orphan*/  CS1A (int) ; 
 scalar_t__ cx_probe_2x_board (int) ; 
 scalar_t__ cx_probe_800_chained_board (int) ; 
 scalar_t__ cx_probe_chained_board (int,int*,int*) ; 
 int /*<<< orphan*/  cx_probe_chip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmatab ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqtab ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  porttab ; 
 int /*<<< orphan*/  valid (int,int /*<<< orphan*/ ) ; 

int cx_probe_board (port_t port, int irq, int dma)
{
	int c0, c1, c2=0, c3=0, result;

	if (! valid (port, porttab))
		return 0;

	if (irq > 0 && ! valid (irq, irqtab))
		return 0;

	if (dma > 0 && ! valid (dma, dmatab))
		return 0;

	if (cx_probe_800_chained_board (port)) {
		/* Sigma-800 detected. */
		if (! (inb (BSR(port)) & BSR_NOCHAIN)) {
			/* chained board attached */
			if (! cx_probe_800_chained_board (port+0x10))
				/* invalid chained board? */
				return (0);
			if (! (inb (BSR(port+0x10)) & BSR_NOCHAIN))
				/* invalid chained board flag? */
				return (0);
		}
		return 1;
	}
	if (cx_probe_chained_board (port, &c0, &c1)) {
		/* Sigma-XXX detected. */
		if (! (inb (BSR(port)) & BSR_NOCHAIN)) {
			/* chained board attached */
			if (! cx_probe_chained_board (port+0x10, &c2, &c3))
				/* invalid chained board? */
				return (0);
			if (! (inb (BSR(port+0x10)) & BSR_NOCHAIN))
				/* invalid chained board flag? */
				return (0);
		}
	} else if (cx_probe_2x_board (port)) {
		c0 = 1;		/* Sigma-2x detected. */
		c1 = 0;
	} else
		return (0);     /* no board detected */

	/* Turn off the reset bit. */
	outb (BCR0(port), BCR0_NORESET);
	if (c2 || c3)
		outb (BCR0(port + 0x10), BCR0_NORESET);

	result = 1;
	if (c0 && ! cx_probe_chip (CS0(port)))
		result = 0;	/* no CD2400 chip here */
	else if (c1 && ! cx_probe_chip (CS1A(port)) &&
	    ! cx_probe_chip (CS1(port)))
		result = 0;	/* no second CD2400 chip */
	else if (c2 && ! cx_probe_chip (CS0(port + 0x10)))
		result = 0;	/* no CD2400 chip on the slave board */
	else if (c3 && ! cx_probe_chip (CS1(port + 0x10)))
		result = 0;	/* no second CD2400 chip on the slave board */

	/* Reset the controller. */
	outb (BCR0(port), 0);
	if (c2 || c3)
		outb (BCR0(port + 0x10), 0);

	/* Yes, we really have valid Sigma board. */
	return (result);
}