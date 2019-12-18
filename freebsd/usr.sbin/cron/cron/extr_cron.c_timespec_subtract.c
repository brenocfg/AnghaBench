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
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static void
timespec_subtract(struct timespec *result, struct timespec *x,
    struct timespec *y)
{
	*result = *x;
	result->tv_sec -= y->tv_sec;
	result->tv_nsec -= y->tv_nsec;
	if (result->tv_nsec < 0) {
		result->tv_sec--;
		result->tv_nsec += 1000000000;
	}
}