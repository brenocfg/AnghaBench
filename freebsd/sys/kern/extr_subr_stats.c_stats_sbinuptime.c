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
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC_FAST ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  sbinuptime () ; 
 int /*<<< orphan*/  tstosbt (struct timespec) ; 

__attribute__((used)) static inline sbintime_t
stats_sbinuptime(void)
{
	sbintime_t sbt;
#ifdef _KERNEL

	sbt = sbinuptime();
#else /* ! _KERNEL */
	struct timespec tp;

	clock_gettime(CLOCK_MONOTONIC_FAST, &tp);
	sbt = tstosbt(tp);
#endif /* _KERNEL */

	return (sbt);
}