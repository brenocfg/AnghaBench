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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */

__attribute__((used)) static void
timeval_add(struct timeval* d, const struct timeval* add)
{
#ifndef S_SPLINT_S
	d->tv_sec += add->tv_sec;
	d->tv_usec += add->tv_usec;
	if(d->tv_usec > 1000000 ) {
		d->tv_usec -= 1000000;
		d->tv_sec++;
	}
#endif
}