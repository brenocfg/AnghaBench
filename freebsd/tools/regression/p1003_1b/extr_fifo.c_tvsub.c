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
struct timeval {long tv_sec; long tv_usec; } ;

/* Variables and functions */

__attribute__((used)) static double
tvsub(const struct timeval *a, const struct timeval *b)
{
	long sdiff;
	long udiff;

	sdiff = a->tv_sec - b->tv_sec;
	udiff = a->tv_usec - b->tv_usec;

	return (double)(sdiff * 1000000 + udiff) / 1e6;
}