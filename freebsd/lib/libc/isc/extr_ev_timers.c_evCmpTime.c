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
struct timespec {long tv_sec; long tv_nsec; } ;

/* Variables and functions */

int
evCmpTime(struct timespec a, struct timespec b) {
	long x = a.tv_sec - b.tv_sec;

	if (x == 0L)
		x = a.tv_nsec - b.tv_nsec;
	return (x < 0L ? (-1) : x > 0L ? (1) : (0));
}