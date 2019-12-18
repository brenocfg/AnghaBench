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
 scalar_t__ BILLION ; 

struct timespec
evSubTime(struct timespec minuend, struct timespec subtrahend) {
	struct timespec x;

	x.tv_sec = minuend.tv_sec - subtrahend.tv_sec;
	if (minuend.tv_nsec >= subtrahend.tv_nsec)
		x.tv_nsec = minuend.tv_nsec - subtrahend.tv_nsec;
	else {
		x.tv_nsec = BILLION - subtrahend.tv_nsec + minuend.tv_nsec;
		x.tv_sec--;
	}
	return (x);
}