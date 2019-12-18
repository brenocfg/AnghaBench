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
 unsigned long PSR_IT_MASK ; 

__attribute__((used)) static inline unsigned long it_advance(unsigned long cpsr)
	{
	if ((cpsr & 0x06000400) == 0) {
		/* ITSTATE<2:0> == 0 means end of IT block, so clear IT state */
		cpsr &= ~PSR_IT_MASK;
	} else {
		/* We need to shift left ITSTATE<4:0> */
		const unsigned long mask = 0x06001c00;  /* Mask ITSTATE<4:0> */
		unsigned long it = cpsr & mask;
		it <<= 1;
		it |= it >> (27 - 10);  /* Carry ITSTATE<2> to correct place */
		it &= mask;
		cpsr &= ~mask;
		cpsr |= it;
	}
	return cpsr;
}