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
struct timeval {int tv_sec; int tv_usec; } ;
struct sockaddr {int dummy; } ;
struct nameserver {int state; int failed_times; int /*<<< orphan*/  address; int /*<<< orphan*/  timeout_event; TYPE_1__* base; } ;
typedef  int /*<<< orphan*/  addrbuf ;
struct TYPE_2__ {int /*<<< orphan*/  global_nameserver_probe_initial_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  EVDNS_LOG_WARN ; 
 int MAX_PROBE_TIMEOUT ; 
 int TIMEOUT_BACKOFF_FACTOR ; 
 scalar_t__ evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_format_sockaddr_port_ (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct timeval*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
nameserver_probe_failed(struct nameserver *const ns) {
	struct timeval timeout;
	int i;

	ASSERT_LOCKED(ns->base);
	(void) evtimer_del(&ns->timeout_event);
	if (ns->state == 1) {
		/* This can happen if the nameserver acts in a way which makes us mark */
		/* it as bad and then starts sending good replies. */
		return;
	}

#define MAX_PROBE_TIMEOUT 3600
#define TIMEOUT_BACKOFF_FACTOR 3

	memcpy(&timeout, &ns->base->global_nameserver_probe_initial_timeout,
	    sizeof(struct timeval));
	for (i=ns->failed_times; i > 0 && timeout.tv_sec < MAX_PROBE_TIMEOUT; --i) {
		timeout.tv_sec *= TIMEOUT_BACKOFF_FACTOR;
		timeout.tv_usec *= TIMEOUT_BACKOFF_FACTOR;
		if (timeout.tv_usec > 1000000) {
			timeout.tv_sec += timeout.tv_usec / 1000000;
			timeout.tv_usec %= 1000000;
		}
	}
	if (timeout.tv_sec > MAX_PROBE_TIMEOUT) {
		timeout.tv_sec = MAX_PROBE_TIMEOUT;
		timeout.tv_usec = 0;
	}

	ns->failed_times++;

	if (evtimer_add(&ns->timeout_event, &timeout) < 0) {
		char addrbuf[128];
		log(EVDNS_LOG_WARN,
		    "Error from libevent when adding timer event for %s",
		    evutil_format_sockaddr_port_(
			    (struct sockaddr *)&ns->address,
			    addrbuf, sizeof(addrbuf)));
	}
}