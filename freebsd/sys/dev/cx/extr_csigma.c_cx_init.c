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
typedef  scalar_t__ port_t ;
typedef  int /*<<< orphan*/  cx_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCR0 (scalar_t__) ; 
 int /*<<< orphan*/  BCR0_NORESET ; 
 int /*<<< orphan*/  BSR (scalar_t__) ; 
 int BSR2X_OSC_33 ; 
 int BSR2X_VAR_MASK ; 
 int BSR_NOCHAIN ; 
 int BSR_OSC_MASK ; 
 int BSR_VAR_MASK ; 
 int CRONYX_22 ; 
 int CRONYX_24 ; 
 int REVCL31_MAX ; 
 int REVCL31_MIN ; 
 int cx_chip_revision (scalar_t__,int) ; 
 int /*<<< orphan*/  cx_init_2x (int /*<<< orphan*/ *,int,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  cx_init_800 (int /*<<< orphan*/ *,int,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  cx_init_board (int /*<<< orphan*/ *,int,scalar_t__,int,int,int,int,int,int,int,int,int) ; 
 scalar_t__ cx_probe_800_chained_board (scalar_t__) ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx_init (cx_board_t *b, int num, port_t port, int irq, int dma)
{
	int gfrcr, rev, chain, mod = 0, rev2 = 0, mod2 = 0;

	rev = inb (BSR(port));
	chain = ! (rev & BSR_NOCHAIN);
	if (cx_probe_800_chained_board (port)) {
		cx_init_800 (b, num, port, irq, dma, chain);
		return;
	}
	if ((rev & BSR2X_VAR_MASK) == CRONYX_22 ||
	    (rev & BSR2X_VAR_MASK) == CRONYX_24) {
		cx_init_2x (b, num, port, irq, dma,
			(rev & BSR2X_VAR_MASK), (rev & BSR2X_OSC_33));
		return;
        }

	outb (BCR0(port), BCR0_NORESET);
	if (chain)
		outb (BCR0(port+0x10), BCR0_NORESET);
	gfrcr = cx_chip_revision (port, rev);
	if (gfrcr >= REVCL31_MIN && gfrcr <= REVCL31_MAX)
		mod = 1;
	if (chain) {
		rev2 = inb (BSR(port+0x10));
		gfrcr = cx_chip_revision (port+0x10, rev2);
		if (gfrcr >= REVCL31_MIN && gfrcr <= REVCL31_MAX)
			mod2 = 1;
		outb (BCR0(port+0x10), 0);
	}
	outb (BCR0(port), 0);

	cx_init_board (b, num, port, irq, dma, chain,
		(rev & BSR_VAR_MASK), (rev & BSR_OSC_MASK), mod,
		(rev2 & BSR_VAR_MASK), (rev2 & BSR_OSC_MASK), mod2);
}