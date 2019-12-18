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
 int const WALLSIG ; 
 int const WALTSIG ; 
 int const WCONTINUED ; 
 int const WEXITED ; 
 int const WNOWAIT ; 
 int const WSTOPPED ; 
 int const WTRAPPED ; 
 int const WUNTRACED ; 
 size_t __BIT (size_t) ; 
 int const __WALL ; 
 int const __WCLONE ; 
 size_t __arraycount (int const*) ; 

__attribute__((used)) static int
get_options4(size_t pos)
{
	int rv = 0;
	size_t n;

	const int special[] = {
		0,
#ifdef	__NetBSD__
		WALLSIG,
		WALTSIG,
		__WALL,		/* Linux compatibility, equal to WALLSIG */
		__WCLONE	/* Linux compatibility, equal to WALTSIG */
#endif
	};

	const int matrix[] = {
		WNOWAIT,
		WEXITED,
		WUNTRACED,
		WSTOPPED,	/* SUS compatibility, equal to WUNTRACED */
		WTRAPPED,
		WCONTINUED
	};

	const size_t M = (1 << __arraycount(special)) - 1;

	if (pos < __arraycount(special))
		return special[pos];

	pos -= __arraycount(special);

	++pos; /* Don't start with empty mask */

	if (pos > M)
		return -1;

	for (n = 0; n < __arraycount(special); n++) {
		if (pos & __BIT(n))
			rv |= matrix[n];
	}

	return rv;
}