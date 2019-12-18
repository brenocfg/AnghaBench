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
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */

__attribute__((used)) static void
tv_add(struct timeval *a, struct timeval const *b)
{
	a->tv_sec += b->tv_sec;
	a->tv_usec += b->tv_usec;

	if(a->tv_usec >= 1000000) {
		a->tv_usec -= 1000000;
		a->tv_sec += 1;
	}
}