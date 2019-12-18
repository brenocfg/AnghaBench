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
struct TYPE_2__ {int /*<<< orphan*/  dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct packed_rrset_data {scalar_t__ ttl; } ;
struct lruhash_entry {scalar_t__ data; scalar_t__ key; } ;
struct del_info {scalar_t__ expired; int /*<<< orphan*/  num_rrsets; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ dname_subdomain_c (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zone_del_rrset(struct lruhash_entry* e, void* arg)
{
	/* entry is locked */
	struct del_info* inf = (struct del_info*)arg;
	struct ub_packed_rrset_key* k = (struct ub_packed_rrset_key*)e->key;
	if(dname_subdomain_c(k->rk.dname, inf->name)) {
		struct packed_rrset_data* d = 
			(struct packed_rrset_data*)e->data;
		if(d->ttl > inf->expired) {
			d->ttl = inf->expired;
			inf->num_rrsets++;
		}
	}
}