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
 int const WCONTINUED ; 
 int const WEXITED ; 
 int const WNOWAIT ; 
 int const WSTOPPED ; 
 int const WTRAPPED ; 
 int const WUNTRACED ; 
 size_t __BIT (size_t) ; 
 size_t __arraycount (int const*) ; 

__attribute__((used)) static int
get_options6(size_t pos)
{
	int rv = 0;
	size_t n;

	/*
	 * waitid(2) must specify at least one of WEXITED, WUNTRACED,
	 * WSTOPPED, WTRAPPED or WCONTINUED. Single option WNOWAIT
	 * isn't valid.
	 */

	const int matrix[] = {
		WNOWAIT,	/* First in order to blacklist it easily */
		WEXITED,
		WUNTRACED,
		WSTOPPED,	/* SUS compatibility, equal to WUNTRACED */
		WTRAPPED,
		WCONTINUED
	};

	const size_t M = (1 << __arraycount(matrix)) - 1;

	/* Skip empty and sole WNOWAIT option */
	pos+=2;

	if (pos > M)
		return -1;

	for (n = 0; n < __arraycount(matrix); n++) {
		if (pos & __BIT(n))
			rv |= matrix[n];
	}

	return rv;
}