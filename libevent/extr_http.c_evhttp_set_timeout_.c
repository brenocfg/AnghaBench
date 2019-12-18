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
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  evutil_timerclear (struct timeval*) ; 

__attribute__((used)) static void
evhttp_set_timeout_(struct timeval *tv, int timeout, int def)
{
	if (timeout == -1) {
		timeout = def;
	}

	if (timeout == -1) {
		evutil_timerclear(tv);
	} else {
		struct timeval timeout_tv;
		timeout_tv.tv_sec = timeout;
		timeout_tv.tv_usec = 0;
		*tv = timeout_tv;
	}
}