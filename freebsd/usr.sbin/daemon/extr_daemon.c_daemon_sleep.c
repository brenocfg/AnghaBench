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
typedef  int /*<<< orphan*/  time_t ;
struct timespec {long member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int nanosleep (struct timespec*,struct timespec*) ; 
 int /*<<< orphan*/  terminate ; 

__attribute__((used)) static void
daemon_sleep(time_t secs, long nsecs)
{
	struct timespec ts = { secs, nsecs };

	while (!terminate && nanosleep(&ts, &ts) == -1) {
		if (errno != EINTR)
			err(1, "nanosleep");
	}
}