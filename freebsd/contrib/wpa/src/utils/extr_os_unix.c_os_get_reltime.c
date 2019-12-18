#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
struct timespec {int tv_nsec; void* tv_sec; } ;
struct os_reltime {int usec; void* sec; } ;
struct TYPE_3__ {void* denom; void* numer; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ mach_timebase_info_data_t ;
typedef  int clockid_t ;

/* Variables and functions */
#define  CLOCK_BOOTTIME 130 
#define  CLOCK_MONOTONIC 129 
#define  CLOCK_REALTIME 128 
 scalar_t__ KERN_SUCCESS ; 
 void* NSEC_PER_SEC ; 
 void* NSEC_PER_USEC ; 
 scalar_t__ TEST_FAIL () ; 
 int clock_gettime (int,struct timespec*) ; 
 void* mach_absolute_time () ; 
 scalar_t__ mach_timebase_info (TYPE_1__*) ; 

int os_get_reltime(struct os_reltime *t)
{
#ifndef __MACH__
#if defined(CLOCK_BOOTTIME)
	static clockid_t clock_id = CLOCK_BOOTTIME;
#elif defined(CLOCK_MONOTONIC)
	static clockid_t clock_id = CLOCK_MONOTONIC;
#else
	static clockid_t clock_id = CLOCK_REALTIME;
#endif
	struct timespec ts;
	int res;

	if (TEST_FAIL())
		return -1;

	while (1) {
		res = clock_gettime(clock_id, &ts);
		if (res == 0) {
			t->sec = ts.tv_sec;
			t->usec = ts.tv_nsec / 1000;
			return 0;
		}
		switch (clock_id) {
#ifdef CLOCK_BOOTTIME
		case CLOCK_BOOTTIME:
			clock_id = CLOCK_MONOTONIC;
			break;
#endif
#ifdef CLOCK_MONOTONIC
		case CLOCK_MONOTONIC:
			clock_id = CLOCK_REALTIME;
			break;
#endif
		case CLOCK_REALTIME:
			return -1;
		}
	}
#else /* __MACH__ */
	uint64_t abstime, nano;
	static mach_timebase_info_data_t info = { 0, 0 };

	if (!info.denom) {
		if (mach_timebase_info(&info) != KERN_SUCCESS)
			return -1;
	}

	abstime = mach_absolute_time();
	nano = (abstime * info.numer) / info.denom;

	t->sec = nano / NSEC_PER_SEC;
	t->usec = (nano - (((uint64_t) t->sec) * NSEC_PER_SEC)) / NSEC_PER_USEC;

	return 0;
#endif /* __MACH__ */
}