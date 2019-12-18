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
struct timeval {long tv_sec; int tv_usec; } ;

/* Variables and functions */

long
timeval_msec_diff(const struct timeval *start, const struct timeval *end)
{
	long ms = end->tv_sec - start->tv_sec;
	ms *= 1000;
	ms += ((end->tv_usec - start->tv_usec)+500) / 1000;
	return ms;
}