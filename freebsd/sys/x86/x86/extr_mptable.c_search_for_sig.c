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
typedef  scalar_t__ u_int32_t ;

/* Variables and functions */
 scalar_t__ BIOS_PADDRTOVADDR (scalar_t__) ; 
 scalar_t__ MP_SIG ; 

__attribute__((used)) static int
search_for_sig(u_int32_t target, int count)
{
	int     x;
	u_int32_t *addr;

	addr = (u_int32_t *)BIOS_PADDRTOVADDR(target);
	for (x = 0; x < count; x += 4)
		if (addr[x] == MP_SIG)
			/* make array index a byte index */
			return (target + (x * sizeof(u_int32_t)));
	return (-1);
}