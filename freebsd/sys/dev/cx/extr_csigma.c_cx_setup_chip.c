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
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ cx_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  BERCNT (int /*<<< orphan*/ ) ; 
 int BRD_INTR_LEVEL ; 
 int /*<<< orphan*/  DMR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPILR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPILR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPILR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cx_setup_chip (cx_chan_t *c)
{
	/* Reset the chip. */
	cx_reset (c->port);

	/*
	 * Set all interrupt level registers to the same value.
	 * This enables the internal CD2400 priority scheme.
	 */
	outb (RPILR(c->port), BRD_INTR_LEVEL);
	outb (TPILR(c->port), BRD_INTR_LEVEL);
	outb (MPILR(c->port), BRD_INTR_LEVEL);

	/* Set bus error count to zero. */
	outb (BERCNT(c->port), 0);

	/* Set 16-bit DMA mode. */
	outb (DMR(c->port), 0);

	/* Set timer period register to 1 msec (approximately). */
	outb (TPR(c->port), 10);
}