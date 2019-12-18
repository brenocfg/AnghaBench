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

/* Variables and functions */
 unsigned int CHAR_BIT ; 

int
isc_tsmemcmp(const void *p1, const void *p2, size_t nb) {
	const unsigned char *ucp1 = p1;
	const unsigned char *ucp2 = p2;
	unsigned int isLT = 0u;
	unsigned int isGT = 0u;
	volatile unsigned int mask = (1u << CHAR_BIT);

	for (/*NOP*/; 0 != nb; --nb, ++ucp1, ++ucp2) {
		isLT |= mask &
		    ((unsigned int)*ucp1 - (unsigned int)*ucp2);
		isGT |= mask &
		    ((unsigned int)*ucp2 - (unsigned int)*ucp1);
		mask &= ~(isLT | isGT);
	}
	return (int)(isGT >> CHAR_BIT) - (int)(isLT >> CHAR_BIT);
}