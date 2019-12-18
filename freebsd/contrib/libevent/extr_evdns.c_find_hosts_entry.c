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
struct hosts_entry {int /*<<< orphan*/  hostname; } ;
struct evdns_base {int /*<<< orphan*/  hostsdb; } ;

/* Variables and functions */
 struct hosts_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 struct hosts_entry* TAILQ_NEXT (struct hosts_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_ascii_strcasecmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  next ; 

__attribute__((used)) static struct hosts_entry *
find_hosts_entry(struct evdns_base *base, const char *hostname,
    struct hosts_entry *find_after)
{
	struct hosts_entry *e;

	if (find_after)
		e = TAILQ_NEXT(find_after, next);
	else
		e = TAILQ_FIRST(&base->hostsdb);

	for (; e; e = TAILQ_NEXT(e, next)) {
		if (!evutil_ascii_strcasecmp(e->hostname, hostname))
			return e;
	}
	return NULL;
}