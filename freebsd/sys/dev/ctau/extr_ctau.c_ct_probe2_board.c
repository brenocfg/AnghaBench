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
 int /*<<< orphan*/  BSR3 (int /*<<< orphan*/ ) ; 
 unsigned char BSR3_IB ; 
 unsigned char BSR3_IB_NEG ; 
 unsigned char BSR3_ZERO ; 
 unsigned char inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  porttab ; 
 int /*<<< orphan*/  valid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ct_probe2_board (port_t port)
{
	unsigned char sr3, osr3;
	int i;

	if (! valid (port, porttab))
		return 0;

	osr3 = inb (BSR3(port));
	if ((osr3 & (BSR3_IB | BSR3_IB_NEG)) != BSR3_IB &&
	    (osr3 & (BSR3_IB | BSR3_IB_NEG)) != BSR3_IB_NEG)
		return (0);
	for (i=0; i<100; ++i) {
		/* Do it twice */
		sr3 = inb (BSR3(port));
		sr3 = inb (BSR3(port));
		if (((sr3 ^ osr3) & (BSR3_IB | BSR3_IB_NEG | BSR3_ZERO)) !=
		    (BSR3_IB | BSR3_IB_NEG))
			return (0);
		osr3 = sr3;
	}
	/* Reset the controller. */
	outb (BCR0(port), 0);
	return 1;
}