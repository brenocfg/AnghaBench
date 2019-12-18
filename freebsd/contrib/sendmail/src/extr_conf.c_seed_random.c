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
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ CurrentPid ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 int /*<<< orphan*/  srandom (long) ; 
 int /*<<< orphan*/  srandomdev () ; 

void
seed_random()
{
#if HASSRANDOMDEV
	srandomdev();
#else /* HASSRANDOMDEV */
	long seed;
	struct timeval t;

	seed = (long) CurrentPid;
	if (gettimeofday(&t, NULL) >= 0)
		seed += t.tv_sec + t.tv_usec;

# if HASRANDOM
	(void) srandom(seed);
# else /* HASRANDOM */
	(void) srand((unsigned int) seed);
# endif /* HASRANDOM */
#endif /* HASSRANDOMDEV */
}