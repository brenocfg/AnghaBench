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

__attribute__((used)) static unsigned int
hash(const char *p)
{
	/* A 32-bit version of Peter Weinberger's (PJW) hash algorithm,
	   as used by ELF for hashing function names. */
	unsigned g, h = 0;
	while (*p != '\0') {
		h = (h << 4) + *p++;
		if ((g = h & 0xF0000000) != 0) {
			h ^= g >> 24;
			h &= 0x0FFFFFFF;
		}
	}
	return h;
}