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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_2__ {scalar_t__ count; } ;
struct val_neg_zone {int /*<<< orphan*/  dclass; TYPE_1__ tree; scalar_t__ labs; int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct val_neg_data {int /*<<< orphan*/  len; int /*<<< orphan*/  name; struct val_neg_data* parent; int /*<<< orphan*/  in_use; } ;
struct ub_packed_rrset_key {int dummy; } ;
struct rrset_cache {int dummy; } ;
struct regional {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_NSEC3 ; 
 struct ub_packed_rrset_key* grab_nsec (struct rrset_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neg_closest_data (struct val_neg_zone*,int /*<<< orphan*/ *,size_t,scalar_t__,struct val_neg_data**) ; 
 int /*<<< orphan*/  neg_params_ok (struct val_neg_zone*,struct ub_packed_rrset_key*) ; 
 size_t nsec3_hash_to_b32 (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ rbtree_last (TYPE_1__*) ; 

__attribute__((used)) static struct ub_packed_rrset_key*
neg_nsec3_getnc(struct val_neg_zone* zone, uint8_t* hashnc, size_t nclen,
	struct rrset_cache* rrset_cache, struct regional* region, 
	time_t now, uint8_t* b32, size_t maxb32)
{
	struct ub_packed_rrset_key* nc_rrset;
	struct val_neg_data* data;
	size_t b32len;

	if(!(b32len=nsec3_hash_to_b32(hashnc, nclen, zone->name,
		zone->len, b32, maxb32)))
		return NULL;
	(void)neg_closest_data(zone, b32, b32len, zone->labs+1, &data);
	if(!data && zone->tree.count != 0) {
		/* could be before the first entry ; return the last
		 * entry (possibly the rollover nsec3 at end) */
		data = (struct val_neg_data*)rbtree_last(&zone->tree);
	}
	while(data && !data->in_use)
		data = data->parent;
	if(!data)
		return NULL;
	/* got a data element in tree, grab it */
	nc_rrset = grab_nsec(rrset_cache, data->name, data->len, 
		LDNS_RR_TYPE_NSEC3, zone->dclass, 0, region, 0, 0, now);
	if(!nc_rrset)
		return NULL;
	if(!neg_params_ok(zone, nc_rrset))
		return NULL;
	return nc_rrset;
}