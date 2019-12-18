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
 int /*<<< orphan*/  _POSIX_VERSION ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int p26(int ac, char *av[])
{
	int ret = 0;

	#ifndef _POSIX_VERSION
	printf("POSIX is not supported.\n");
	ret = -1;
	#else	/* _POSIX_VERSION */

	#if (_POSIX_VERSION == 198808L)
	printf("POSIX.1 is supported but not POSIX.1B (FIPS 151-1)\n");
	#elif (_POSIX_VERSION == 199009L)
	printf("POSIX.1 is supported but not POSIX.1B (FIPS 151-2)\n");
	#elif (_POSIX_VERSION >= 199309L)
	printf("POSIX.1 and POSIX.1B are supported.\n");
	#else
	printf("_POSIX_VERSION (%ld) not 198808, 199009, or >= 199309.\n",
		_POSIX_VERSION);
	ret = -1;
	#endif

	#endif	/* _POSIX_VERSION */
	return ret;
}