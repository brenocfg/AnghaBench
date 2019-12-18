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
struct timeval {int dummy; } ;
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIMEVAL_TO_TIMESPEC (struct timeval*,struct timespec*) ; 
#define  TSP_HZ 131 
#define  TSP_NSEC 130 
#define  TSP_SEC 129 
#define  TSP_USEC 128 
 int /*<<< orphan*/  getnanotime (struct timespec*) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 
 int /*<<< orphan*/  time_second ; 
 int timestamp_precision ; 

void
vfs_timestamp(struct timespec *tsp)
{
	struct timeval tv;

	switch (timestamp_precision) {
	case TSP_SEC:
		tsp->tv_sec = time_second;
		tsp->tv_nsec = 0;
		break;
	case TSP_HZ:
		getnanotime(tsp);
		break;
	case TSP_USEC:
		microtime(&tv);
		TIMEVAL_TO_TIMESPEC(&tv, tsp);
		break;
	case TSP_NSEC:
	default:
		nanotime(tsp);
		break;
	}
}