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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct val_neg_zone {int /*<<< orphan*/  dclass; int /*<<< orphan*/  name; scalar_t__ nsec3_hash; struct val_neg_zone* parent; int /*<<< orphan*/  in_use; } ;
struct val_neg_data {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  in_use; } ;
struct val_neg_cache {int /*<<< orphan*/  lock; } ;
struct ub_packed_rrset_key {int dummy; } ;
struct rrset_cache {int dummy; } ;
struct regional {int dummy; } ;
typedef  int /*<<< orphan*/  rbnode_type ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_NSEC ; 
 scalar_t__ PACKED_RRSET_NSEC_AT_APEX ; 
 int /*<<< orphan*/ * RBTREE_NULL ; 
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 struct ub_packed_rrset_key* grab_nsec (struct rrset_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neg_closest_data (struct val_neg_zone*,int /*<<< orphan*/ *,size_t,int,struct val_neg_data**) ; 
 struct val_neg_zone* neg_closest_zone_parent (struct val_neg_cache*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rbtree_previous (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ub_packed_rrset_key*
neg_find_nsec(struct val_neg_cache* neg_cache, uint8_t* qname, size_t qname_len,
	uint16_t qclass, struct rrset_cache* rrset_cache, time_t now,
	struct regional* region)
{
	int labs;
	uint32_t flags;
	struct val_neg_zone* zone;
	struct val_neg_data* data;
	struct ub_packed_rrset_key* nsec;

	labs = dname_count_labels(qname);
	lock_basic_lock(&neg_cache->lock);
	zone = neg_closest_zone_parent(neg_cache, qname, qname_len, labs,
		qclass);
	while(zone && !zone->in_use)
		zone = zone->parent;
	if(!zone) {
		lock_basic_unlock(&neg_cache->lock);
		return NULL;
	}

	/* NSEC only for now */
	if(zone->nsec3_hash) {
		lock_basic_unlock(&neg_cache->lock);
		return NULL;
	}

	/* ignore return value, don't care if it is an exact or smaller match */
	(void)neg_closest_data(zone, qname, qname_len, labs, &data);
	if(!data) {
		lock_basic_unlock(&neg_cache->lock);
		return NULL;
	}

	/* ENT nodes are not in use, try the previous node. If the previous node
	 * is not in use, we don't have an useful NSEC and give up. */
	if(!data->in_use) {
		data = (struct val_neg_data*)rbtree_previous((rbnode_type*)data);
		if((rbnode_type*)data == RBTREE_NULL || !data->in_use) {
			lock_basic_unlock(&neg_cache->lock);
			return NULL;
		}
	}

	flags = 0;
	if(query_dname_compare(data->name, zone->name) == 0)
		flags = PACKED_RRSET_NSEC_AT_APEX;

	nsec = grab_nsec(rrset_cache, data->name, data->len, LDNS_RR_TYPE_NSEC,
		zone->dclass, flags, region, 0, 0, now);
	lock_basic_unlock(&neg_cache->lock);
	return nsec;
}