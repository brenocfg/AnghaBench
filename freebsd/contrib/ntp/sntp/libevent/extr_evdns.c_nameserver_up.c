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
struct sockaddr {int dummy; } ;
struct nameserver {int state; TYPE_1__* base; scalar_t__ timedout; scalar_t__ failed_times; int /*<<< orphan*/ * probe_request; int /*<<< orphan*/  timeout_event; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  addrbuf ;
struct TYPE_3__ {int /*<<< orphan*/  global_good_nameservers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  EVDNS_LOG_MSG ; 
 int /*<<< orphan*/  evdns_cancel_request (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evutil_format_sockaddr_port_ (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nameserver_up(struct nameserver *const ns)
{
	char addrbuf[128];
	ASSERT_LOCKED(ns->base);
	if (ns->state) return;
	log(EVDNS_LOG_MSG, "Nameserver %s is back up",
	    evutil_format_sockaddr_port_(
		    (struct sockaddr *)&ns->address,
		    addrbuf, sizeof(addrbuf)));
	evtimer_del(&ns->timeout_event);
	if (ns->probe_request) {
		evdns_cancel_request(ns->base, ns->probe_request);
		ns->probe_request = NULL;
	}
	ns->state = 1;
	ns->failed_times = 0;
	ns->timedout = 0;
	ns->base->global_good_nameservers++;
}