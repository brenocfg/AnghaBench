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
 unsigned int PPC_BITLSHIFT (int) ; 

__attribute__((used)) static inline void tlbiel_hash_set_isa206(unsigned int set, unsigned int is)
{
	unsigned long rb;

	rb = (set << PPC_BITLSHIFT(51)) | (is << PPC_BITLSHIFT(53));

	asm volatile("tlbiel %0" : : "r" (rb));
}