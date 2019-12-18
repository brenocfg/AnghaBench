#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {scalar_t__ count; } ;
struct val_neg_zone {TYPE_2__ tree; int /*<<< orphan*/ * name; } ;
struct val_neg_cache {int /*<<< orphan*/  lock; } ;
struct reply_info {size_t an_numrrsets; size_t ns_numrrsets; TYPE_3__** rrsets; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dname; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {TYPE_1__ rk; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_NS ; 
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 size_t calc_data_need (struct reply_info*) ; 
 size_t calc_zone_need (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  dname_subdomain_c (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct val_neg_zone* neg_create_zone (struct val_neg_cache*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neg_delete_zone (struct val_neg_cache*,struct val_neg_zone*) ; 
 struct val_neg_zone* neg_find_zone (struct val_neg_cache*,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neg_insert_data (struct val_neg_cache*,struct val_neg_zone*,TYPE_3__*) ; 
 int /*<<< orphan*/  neg_make_space (struct val_neg_cache*,size_t) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * reply_nsec_signer (struct reply_info*,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  val_neg_zone_take_inuse (struct val_neg_zone*) ; 

void val_neg_addreferral(struct val_neg_cache* neg, struct reply_info* rep,
	uint8_t* zone_name)
{
	size_t i, need;
	uint8_t* signer;
	size_t signer_len;
	uint16_t dclass;
	struct val_neg_zone* zone;
	/* no SOA in this message, find RRSIG over NSEC's signer name.
	 * note the NSEC records are maybe not validated yet */
	signer = reply_nsec_signer(rep, &signer_len, &dclass);
	if(!signer) 
		return;
	if(!dname_subdomain_c(signer, zone_name)) {
		/* the signer is not in the bailiwick, throw it out */
		return;
	}

	log_nametypeclass(VERB_ALGO, "negcache insert referral ",
		signer, LDNS_RR_TYPE_NS, dclass);
	
	/* ask for enough space to store all of it */
	need = calc_data_need(rep) + calc_zone_need(signer, signer_len);
	lock_basic_lock(&neg->lock);
	neg_make_space(neg, need);

	/* find or create the zone entry */
	zone = neg_find_zone(neg, signer, signer_len, dclass);
	if(!zone) {
		if(!(zone = neg_create_zone(neg, signer, signer_len, 
			dclass))) {
			lock_basic_unlock(&neg->lock);
			log_err("out of memory adding negative zone");
			return;
		}
	}
	val_neg_zone_take_inuse(zone);

	/* insert the NSECs */
	for(i=rep->an_numrrsets; i< rep->an_numrrsets+rep->ns_numrrsets; i++){
		if(ntohs(rep->rrsets[i]->rk.type) != LDNS_RR_TYPE_NSEC &&
			ntohs(rep->rrsets[i]->rk.type) != LDNS_RR_TYPE_NSEC3)
			continue;
		if(!dname_subdomain_c(rep->rrsets[i]->rk.dname, 
			zone->name)) continue;
		/* insert NSEC into this zone's tree */
		neg_insert_data(neg, zone, rep->rrsets[i]);
	}
	if(zone->tree.count == 0) {
		/* remove empty zone if inserts failed */
		neg_delete_zone(neg, zone);
	}
	lock_basic_unlock(&neg->lock);
}