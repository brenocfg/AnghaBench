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

__attribute__((used)) static inline void __memcpy_unaligned_dn (unsigned long d, unsigned long s,
					  long n)
{
	/* I don't understand AXP assembler well enough for this. -Tim */
	s += n;
	d += n;
	while (n--)
		* (char *) --d = * (char *) --s;
}