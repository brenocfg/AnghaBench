#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_2__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct ntptimeval {int /*<<< orphan*/  time_state; int /*<<< orphan*/  tai; int /*<<< orphan*/  esterror; int /*<<< orphan*/  maxerror; TYPE_1__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  NTP_ASSERT_LOCKED () ; 
 int /*<<< orphan*/  TIME_ERROR ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 
 scalar_t__ ntp_is_time_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_esterror ; 
 int /*<<< orphan*/  time_maxerror ; 
 int /*<<< orphan*/  time_state ; 
 int /*<<< orphan*/  time_status ; 
 int /*<<< orphan*/  time_tai ; 

__attribute__((used)) static void
ntp_gettime1(struct ntptimeval *ntvp)
{
	struct timespec atv;	/* nanosecond time */

	NTP_ASSERT_LOCKED();

	nanotime(&atv);
	ntvp->time.tv_sec = atv.tv_sec;
	ntvp->time.tv_nsec = atv.tv_nsec;
	ntvp->maxerror = time_maxerror;
	ntvp->esterror = time_esterror;
	ntvp->tai = time_tai;
	ntvp->time_state = time_state;

	if (ntp_is_time_error(time_status))
		ntvp->time_state = TIME_ERROR;
}