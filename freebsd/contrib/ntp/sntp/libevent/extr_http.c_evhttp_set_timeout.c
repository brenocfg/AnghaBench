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
struct evhttp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evhttp_set_timeout_tv (struct evhttp*,struct timeval*) ; 

void
evhttp_set_timeout(struct evhttp* http, int timeout_in_secs)
{
	if (timeout_in_secs == -1) {
		evhttp_set_timeout_tv(http, NULL);
	} else {
		struct timeval tv;
		tv.tv_sec = timeout_in_secs;
		tv.tv_usec = 0;
		evhttp_set_timeout_tv(http, &tv);
	}
}