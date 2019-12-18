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
typedef  int /*<<< orphan*/  time_t ;
struct timeval {int /*<<< orphan*/  tv_sec; } ;
struct comm_base {int dummy; } ;
struct TYPE_2__ {scalar_t__ magic; int /*<<< orphan*/ * vmt; } ;

/* Variables and functions */
 scalar_t__ UB_EVENT_MAGIC ; 
 TYPE_1__* comm_base_internal (struct comm_base*) ; 
 int /*<<< orphan*/  comm_base_timept (struct comm_base*,int /*<<< orphan*/ **,struct timeval**) ; 
 int /*<<< orphan*/  default_event_base_vmt ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void ub_comm_base_now(struct comm_base* cb)
{
	time_t *tt;
	struct timeval *tv;

#ifdef USE_MINI_EVENT
/** minievent updates the time when it blocks. */
	if (comm_base_internal(cb)->magic == UB_EVENT_MAGIC &&
	    comm_base_internal(cb)->vmt == &default_event_base_vmt)
		return; /* Actually using mini event, so do not set time */
#endif /* USE_MINI_EVENT */

/** fillup the time values in the event base */
	comm_base_timept(cb, &tt, &tv);
	if(gettimeofday(tv, NULL) < 0) {
		log_err("gettimeofday: %s", strerror(errno));
	}
	*tt = tv->tv_sec;
}