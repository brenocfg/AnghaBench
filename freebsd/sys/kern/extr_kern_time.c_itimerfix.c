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
typedef  int u_int ;
struct timeval {scalar_t__ tv_sec; int tv_usec; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ tick ; 

int
itimerfix(struct timeval *tv)
{

	if (tv->tv_sec < 0 || tv->tv_usec < 0 || tv->tv_usec >= 1000000)
		return (EINVAL);
	if (tv->tv_sec == 0 && tv->tv_usec != 0 &&
	    tv->tv_usec < (u_int)tick / 16)
		tv->tv_usec = (u_int)tick / 16;
	return (0);
}