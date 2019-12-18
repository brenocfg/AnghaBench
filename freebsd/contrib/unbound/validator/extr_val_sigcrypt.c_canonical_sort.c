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
struct ub_packed_rrset_key {int dummy; } ;
struct packed_rrset_data {size_t count; } ;
struct TYPE_2__ {struct canon_rr* key; } ;
struct canon_rr {size_t rr_idx; TYPE_1__ node; struct ub_packed_rrset_key* rrset; } ;
typedef  int /*<<< orphan*/  rbtree_type ;

/* Variables and functions */
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
canonical_sort(struct ub_packed_rrset_key* rrset, struct packed_rrset_data* d,
	rbtree_type* sortree, struct canon_rr* rrs)
{
	size_t i;
	/* insert into rbtree to sort and detect duplicates */
	for(i=0; i<d->count; i++) {
		rrs[i].node.key = &rrs[i];
		rrs[i].rrset = rrset;
		rrs[i].rr_idx = i;
		if(!rbtree_insert(sortree, &rrs[i].node)) {
			/* this was a duplicate */
		}
	}
}