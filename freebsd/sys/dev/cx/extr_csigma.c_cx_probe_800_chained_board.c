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
typedef  int /*<<< orphan*/  port_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCR1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCR2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BDET (int /*<<< orphan*/ ) ; 
 unsigned char BDET_IB ; 
 unsigned char BDET_IB_NEG ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx_probe_800_chained_board (port_t port)
{
	unsigned char det, odet;
	int i;

	odet = inb (BDET(port));
	if ((odet & (BDET_IB | BDET_IB_NEG)) != BDET_IB &&
	    (odet & (BDET_IB | BDET_IB_NEG)) != BDET_IB_NEG)
		return (0);
	for (i=0; i<100; ++i) {
		det = inb (BDET(port));
		if (((det ^ odet) & (BDET_IB | BDET_IB_NEG)) !=
		    (BDET_IB | BDET_IB_NEG))
			return (0);
		odet = det;
	}
	/* Reset the controller. */
	outb (BCR0(port), 0);
	outb (BCR1(port), 0);
	outb (BCR2(port), 0);
	return (1);
}