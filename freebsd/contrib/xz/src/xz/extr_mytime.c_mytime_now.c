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
typedef  int uint64_t ;
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
struct timespec {int tv_nsec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int UINT64_C (int) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
mytime_now(void)
{
	// NOTE: HAVE_DECL_CLOCK_MONOTONIC is always defined to 0 or 1.
#if defined(HAVE_CLOCK_GETTIME) && HAVE_DECL_CLOCK_MONOTONIC
	// If CLOCK_MONOTONIC was available at compile time but for some
	// reason isn't at runtime, fallback to CLOCK_REALTIME which
	// according to POSIX is mandatory for all implementations.
	static clockid_t clk_id = CLOCK_MONOTONIC;
	struct timespec tv;
	while (clock_gettime(clk_id, &tv))
		clk_id = CLOCK_REALTIME;

	return (uint64_t)(tv.tv_sec) * UINT64_C(1000) + tv.tv_nsec / 1000000;
#else
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (uint64_t)(tv.tv_sec) * UINT64_C(1000) + tv.tv_usec / 1000;
#endif
}