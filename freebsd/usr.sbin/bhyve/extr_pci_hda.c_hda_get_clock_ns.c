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
typedef  scalar_t__ uint64_t ;
struct timespec {long long tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 

__attribute__((used)) static uint64_t hda_get_clock_ns(void)
{
	struct timespec ts;
	int err;

	err = clock_gettime(CLOCK_MONOTONIC, &ts);
	assert(!err);

	return (ts.tv_sec * 1000000000LL + ts.tv_nsec);
}