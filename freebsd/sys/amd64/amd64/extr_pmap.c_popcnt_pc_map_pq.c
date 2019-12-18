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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int u_long ;

/* Variables and functions */

__attribute__((used)) static int
popcnt_pc_map_pq(uint64_t *map)
{
	u_long result, tmp;

	__asm __volatile("xorl %k0,%k0;popcntq %2,%0;"
	    "xorl %k1,%k1;popcntq %3,%1;addl %k1,%k0;"
	    "xorl %k1,%k1;popcntq %4,%1;addl %k1,%k0"
	    : "=&r" (result), "=&r" (tmp)
	    : "m" (map[0]), "m" (map[1]), "m" (map[2]));
	return (result);
}