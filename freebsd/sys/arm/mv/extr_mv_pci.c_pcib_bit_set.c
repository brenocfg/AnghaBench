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
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t BITS_PER_UINT32 ; 

__attribute__((used)) static inline void
pcib_bit_set(uint32_t *map, uint32_t bit)
{
	uint32_t n = bit / BITS_PER_UINT32;

	bit = bit % BITS_PER_UINT32;
	map[n] |= (1 << bit);
}