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
struct hosts_entry {int dummy; } ;
struct evdns_base {int /*<<< orphan*/  hostsdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVDNS_LOCK (struct evdns_base*) ; 
 int /*<<< orphan*/  EVDNS_UNLOCK (struct evdns_base*) ; 
 struct hosts_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct hosts_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_free (struct hosts_entry*) ; 
 int /*<<< orphan*/  next ; 

void
evdns_base_clear_host_addresses(struct evdns_base *base)
{
	struct hosts_entry *victim;
	EVDNS_LOCK(base);
	while ((victim = TAILQ_FIRST(&base->hostsdb))) {
		TAILQ_REMOVE(&base->hostsdb, victim, next);
		mm_free(victim);
	}
	EVDNS_UNLOCK(base);
}