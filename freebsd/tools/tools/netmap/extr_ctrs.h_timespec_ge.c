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
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;

/* Variables and functions */

__attribute__((used)) static __inline int
timespec_ge(const struct timespec *a, const struct timespec *b)
{

	if (a->tv_sec > b->tv_sec)
		return (1);
	if (a->tv_sec < b->tv_sec)
		return (0);
	if (a->tv_nsec >= b->tv_nsec)
		return (1);
	return (0);
}