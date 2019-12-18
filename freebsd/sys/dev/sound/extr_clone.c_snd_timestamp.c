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
#define  SND_TSP_HZ 131 
#define  SND_TSP_NSEC 130 
#define  SND_TSP_SEC 129 
#define  SND_TSP_USEC 128 
 int /*<<< orphan*/  TIMEVAL_TO_TIMESPEC (struct timeval*,struct timespec*) ; 
 int /*<<< orphan*/  getnanouptime (struct timespec*) ; 
 int /*<<< orphan*/  microuptime (struct timeval*) ; 
 int /*<<< orphan*/  nanouptime (struct timespec*) ; 
 int snd_timestamp_precision ; 
 int /*<<< orphan*/  time_second ; 

void
snd_timestamp(struct timespec *tsp)
{
	struct timeval tv;

	switch (snd_timestamp_precision) {
	case SND_TSP_SEC:
		tsp->tv_sec = time_second;
		tsp->tv_nsec = 0;
		break;
	case SND_TSP_HZ:
		getnanouptime(tsp);
		break;
	case SND_TSP_USEC:
		microuptime(&tv);
		TIMEVAL_TO_TIMESPEC(&tv, tsp);
		break;
	case SND_TSP_NSEC:
		nanouptime(tsp);
		break;
	default:
		snd_timestamp_precision = SND_TSP_HZ;
		getnanouptime(tsp);
		break;
	}
}