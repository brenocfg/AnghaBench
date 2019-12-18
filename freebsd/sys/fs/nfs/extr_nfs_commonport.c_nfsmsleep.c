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
typedef  int u_int64_t ;
struct timespec {int tv_sec; scalar_t__ tv_nsec; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int hz ; 
 int msleep (void*,struct mtx*,int,char const*,int) ; 

int
nfsmsleep(void *chan, void *mutex, int prio, const char *wmesg,
    struct timespec *ts)
{
	u_int64_t nsecval;
	int error, timeo;

	if (ts) {
		timeo = hz * ts->tv_sec;
		nsecval = (u_int64_t)ts->tv_nsec;
		nsecval = ((nsecval * ((u_int64_t)hz)) + 500000000) /
		    1000000000;
		timeo += (int)nsecval;
	} else {
		timeo = 0;
	}
	error = msleep(chan, (struct mtx *)mutex, prio, wmesg, timeo);
	return (error);
}