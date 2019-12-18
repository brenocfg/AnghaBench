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

__attribute__((used)) static inline bool cpu_signatures_match(unsigned int s1, unsigned int p1,
					unsigned int s2, unsigned int p2)
{
	if (s1 != s2)
		return false;

	/* Processor flags are either both 0 ... */
	if (!p1 && !p2)
		return true;

	/* ... or they intersect. */
	return p1 & p2;
}