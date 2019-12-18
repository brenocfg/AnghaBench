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
timestwo(struct timeval* v)
{
#ifndef S_SPLINT_S
	if(v->tv_sec == 0 && v->tv_usec == 0) {
		v->tv_usec = 1;
		return;
	}
	v->tv_sec *= 2;
	v->tv_usec *= 2;
	if(v->tv_usec == 1024*1024) {
		/* nice values and easy to compute */
		v->tv_sec = 1;
		v->tv_usec = 0;
	}
#endif
}