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
typedef  scalar_t__ u_long ;
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 scalar_t__ arc4random_uniform (int) ; 

void
intvl_random(struct timeval *tp,	/* put value here */
	     u_long lo,			/* value is after this second */
	     u_long hi)			/* and before this */
{
	tp->tv_sec = (time_t)(hi == lo
			      ? lo
			      : (lo + arc4random_uniform(1 + hi - lo)));
	tp->tv_usec = arc4random_uniform(1000000);
}