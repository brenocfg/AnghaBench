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
struct nameserver {int /*<<< orphan*/  base; int /*<<< orphan*/ * probe_request; } ;

/* Variables and functions */
 int DNS_ERR_CANCEL ; 
 int DNS_ERR_NONE ; 
 int DNS_ERR_NOTEXIST ; 
 int /*<<< orphan*/  EVDNS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nameserver_probe_failed (struct nameserver* const) ; 
 int /*<<< orphan*/  nameserver_up (struct nameserver* const) ; 

__attribute__((used)) static void
nameserver_probe_callback(int result, char type, int count, int ttl, void *addresses, void *arg) {
	struct nameserver *const ns = (struct nameserver *) arg;
	(void) type;
	(void) count;
	(void) ttl;
	(void) addresses;

	if (result == DNS_ERR_CANCEL) {
		/* We canceled this request because the nameserver came up
		 * for some other reason.  Do not change our opinion about
		 * the nameserver. */
		return;
	}

	EVDNS_LOCK(ns->base);
	ns->probe_request = NULL;
	if (result == DNS_ERR_NONE || result == DNS_ERR_NOTEXIST) {
		/* this is a good reply */
		nameserver_up(ns);
	} else {
		nameserver_probe_failed(ns);
	}
	EVDNS_UNLOCK(ns->base);
}