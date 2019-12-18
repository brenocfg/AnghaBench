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
struct TYPE_2__ {int flags; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct packed_rrset_data {int count; scalar_t__ rrsig_count; scalar_t__* rr_len; int /*<<< orphan*/  ttl; } ;
struct lruhash_entry {scalar_t__ data; scalar_t__ key; } ;
struct del_info {int /*<<< orphan*/  num_rrsets; int /*<<< orphan*/  expired; } ;

/* Variables and functions */
 int PACKED_RRSET_PARENT_SIDE ; 

__attribute__((used)) static void
negative_del_rrset(struct lruhash_entry* e, void* arg)
{
	/* entry is locked */
	struct del_info* inf = (struct del_info*)arg;
	struct ub_packed_rrset_key* k = (struct ub_packed_rrset_key*)e->key;
	struct packed_rrset_data* d = (struct packed_rrset_data*)e->data;
	/* delete the parentside negative cache rrsets,
	 * these are nameserver rrsets that failed lookup, rdata empty */
	if((k->rk.flags & PACKED_RRSET_PARENT_SIDE) && d->count == 1 &&
		d->rrsig_count == 0 && d->rr_len[0] == 0) {
		d->ttl = inf->expired;
		inf->num_rrsets++;
	}
}