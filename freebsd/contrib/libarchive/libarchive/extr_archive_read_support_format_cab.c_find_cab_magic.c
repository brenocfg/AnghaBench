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
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 

__attribute__((used)) static int
find_cab_magic(const char *p)
{
	switch (p[4]) {
	case 0:
		/*
		 * Note: Self-Extraction program has 'MSCF' string in their
		 * program. If we were finding 'MSCF' string only, we got
		 * wrong place for Cabinet header, thus, we have to check
		 * following four bytes which are reserved and must be set
		 * to zero.
		 */
		if (memcmp(p, "MSCF\0\0\0\0", 8) == 0)
			return 0;
		return 5;
	case 'F': return 1;
	case 'C': return 2;
	case 'S': return 3;
	case 'M': return 4;
	default:  return 5;
	}
}