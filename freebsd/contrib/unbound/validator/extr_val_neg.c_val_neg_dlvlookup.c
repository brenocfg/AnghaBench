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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ time_t ;
struct val_neg_zone {int /*<<< orphan*/  dclass; int /*<<< orphan*/ * name; scalar_t__ nsec3_hash; struct val_neg_zone* parent; int /*<<< orphan*/  in_use; } ;
struct val_neg_data {int /*<<< orphan*/  len; int /*<<< orphan*/ * name; struct val_neg_data* parent; int /*<<< orphan*/  in_use; } ;
struct val_neg_cache {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct rrset_cache {int dummy; } ;
struct query_info {int /*<<< orphan*/ * local_alias; int /*<<< orphan*/  qclass; int /*<<< orphan*/  qtype; int /*<<< orphan*/ * qname; } ;
struct packed_rrset_data {scalar_t__ ttl; scalar_t__ security; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_DLV ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_NSEC ; 
 scalar_t__ PACKED_RRSET_NSEC_AT_APEX ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neg_closest_data (struct val_neg_zone*,int /*<<< orphan*/ *,size_t,int,struct val_neg_data**) ; 
 struct val_neg_zone* neg_closest_zone_parent (struct val_neg_cache*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neg_delete_data (struct val_neg_cache*,struct val_neg_data*) ; 
 int /*<<< orphan*/  neg_lru_touch (struct val_neg_cache*,struct val_neg_data*) ; 
 int /*<<< orphan*/  nsec_proves_nodata (struct ub_packed_rrset_key*,struct query_info*,int /*<<< orphan*/ **) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ub_packed_rrset_key* rrset_cache_lookup (struct rrset_cache*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sec_status_secure ; 
 int /*<<< orphan*/  val_nsec_proves_name_error (struct ub_packed_rrset_key*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

int val_neg_dlvlookup(struct val_neg_cache* neg, uint8_t* qname, size_t len,
        uint16_t qclass, struct rrset_cache* rrset_cache, time_t now)
{
	/* lookup closest zone */
	struct val_neg_zone* zone;
	struct val_neg_data* data;
	int labs;
	struct ub_packed_rrset_key* nsec;
	struct packed_rrset_data* d;
	uint32_t flags;
	uint8_t* wc;
	struct query_info qinfo;
	if(!neg) return 0;

	log_nametypeclass(VERB_ALGO, "negcache dlvlookup", qname, 
		LDNS_RR_TYPE_DLV, qclass);
	
	labs = dname_count_labels(qname);
	lock_basic_lock(&neg->lock);
	zone = neg_closest_zone_parent(neg, qname, len, labs, qclass);
	while(zone && !zone->in_use)
		zone = zone->parent;
	if(!zone) {
		lock_basic_unlock(&neg->lock);
		return 0;
	}
	log_nametypeclass(VERB_ALGO, "negcache zone", zone->name, 0, 
		zone->dclass);

	/* DLV is defined to use NSEC only */
	if(zone->nsec3_hash) {
		lock_basic_unlock(&neg->lock);
		return 0;
	}

	/* lookup closest data record */
	(void)neg_closest_data(zone, qname, len, labs, &data);
	while(data && !data->in_use)
		data = data->parent;
	if(!data) {
		lock_basic_unlock(&neg->lock);
		return 0;
	}
	log_nametypeclass(VERB_ALGO, "negcache rr", data->name, 
		LDNS_RR_TYPE_NSEC, zone->dclass);

	/* lookup rrset in rrset cache */
	flags = 0;
	if(query_dname_compare(data->name, zone->name) == 0)
		flags = PACKED_RRSET_NSEC_AT_APEX;
	nsec = rrset_cache_lookup(rrset_cache, data->name, data->len,
		LDNS_RR_TYPE_NSEC, zone->dclass, flags, now, 0);

	/* check if secure and TTL ok */
	if(!nsec) {
		lock_basic_unlock(&neg->lock);
		return 0;
	}
	d = (struct packed_rrset_data*)nsec->entry.data;
	if(!d || now > d->ttl) {
		lock_rw_unlock(&nsec->entry.lock);
		/* delete data record if expired */
		neg_delete_data(neg, data);
		lock_basic_unlock(&neg->lock);
		return 0;
	}
	if(d->security != sec_status_secure) {
		lock_rw_unlock(&nsec->entry.lock);
		neg_delete_data(neg, data);
		lock_basic_unlock(&neg->lock);
		return 0;
	}
	verbose(VERB_ALGO, "negcache got secure rrset");

	/* check NSEC security */
	/* check if NSEC proves no DLV type exists */
	/* check if NSEC proves NXDOMAIN for qname */
	qinfo.qname = qname;
	qinfo.qtype = LDNS_RR_TYPE_DLV;
	qinfo.qclass = qclass;
	qinfo.local_alias = NULL;
	if(!nsec_proves_nodata(nsec, &qinfo, &wc) &&
		!val_nsec_proves_name_error(nsec, qname)) {
		/* the NSEC is not a denial for the DLV */
		lock_rw_unlock(&nsec->entry.lock);
		lock_basic_unlock(&neg->lock);
		verbose(VERB_ALGO, "negcache not proven");
		return 0;
	}
	/* so the NSEC was a NODATA proof, or NXDOMAIN proof. */

	/* no need to check for wildcard NSEC; no wildcards in DLV repos */
	/* no need to lookup SOA record for client; no response message */

	lock_rw_unlock(&nsec->entry.lock);
	/* if OK touch the LRU for neg_data element */
	neg_lru_touch(neg, data);
	lock_basic_unlock(&neg->lock);
	verbose(VERB_ALGO, "negcache DLV denial proven");
	return 1;
}