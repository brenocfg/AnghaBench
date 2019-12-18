#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ dname_len; scalar_t__ flags; scalar_t__ type; scalar_t__ rrset_class; int /*<<< orphan*/  dname; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; TYPE_1__ entry; } ;
struct packed_rrset_data {size_t count; size_t rrsig_count; scalar_t__ trust; scalar_t__ security; scalar_t__* rr_len; int /*<<< orphan*/ * rr_data; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rrset_equal(struct ub_packed_rrset_key* k1, struct ub_packed_rrset_key* k2)
{
	struct packed_rrset_data* d1 = (struct packed_rrset_data*)
		k1->entry.data;
	struct packed_rrset_data* d2 = (struct packed_rrset_data*)
		k2->entry.data;
	size_t i, t;
	if(k1->rk.dname_len != k2->rk.dname_len ||
		k1->rk.flags != k2->rk.flags ||
		k1->rk.type != k2->rk.type ||
		k1->rk.rrset_class != k2->rk.rrset_class ||
		query_dname_compare(k1->rk.dname, k2->rk.dname) != 0)
		return 0;
	if(	/* do not check ttl: d1->ttl != d2->ttl || */
		d1->count != d2->count ||
		d1->rrsig_count != d2->rrsig_count ||
		d1->trust != d2->trust ||
		d1->security != d2->security)
		return 0;
	t = d1->count + d1->rrsig_count;
	for(i=0; i<t; i++) {
		if(d1->rr_len[i] != d2->rr_len[i] ||
			/* no ttl check: d1->rr_ttl[i] != d2->rr_ttl[i] ||*/
			memcmp(d1->rr_data[i], d2->rr_data[i], 
				d1->rr_len[i]) != 0)
			return 0;
	}
	return 1;
}