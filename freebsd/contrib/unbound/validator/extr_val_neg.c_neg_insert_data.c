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
typedef  int /*<<< orphan*/  uint8_t ;
struct val_neg_zone {int nsec3_hash; size_t nsec3_iter; size_t nsec3_saltlen; int /*<<< orphan*/ * nsec3_salt; int /*<<< orphan*/  tree; } ;
struct val_neg_data {scalar_t__ count; int in_use; struct val_neg_data* parent; int /*<<< orphan*/  node; struct val_neg_zone* zone; scalar_t__ len; int /*<<< orphan*/  name; } ;
struct val_neg_cache {size_t nsec3_max_iter; int /*<<< orphan*/  use; } ;
struct TYPE_4__ {size_t dname_len; int /*<<< orphan*/  type; int /*<<< orphan*/  rrset_class; int /*<<< orphan*/ * dname; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; TYPE_1__ entry; } ;
struct packed_rrset_data {scalar_t__ security; scalar_t__ rrsig_count; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NSEC3 ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * memdup (int /*<<< orphan*/ *,size_t) ; 
 struct val_neg_data* neg_closest_data_parent (struct val_neg_zone*,int /*<<< orphan*/ *,size_t,int) ; 
 struct val_neg_data* neg_data_chain (int /*<<< orphan*/ *,size_t,int,struct val_neg_data*) ; 
 int /*<<< orphan*/  neg_lru_front (struct val_neg_cache*,struct val_neg_data*) ; 
 int /*<<< orphan*/  neg_lru_touch (struct val_neg_cache*,struct val_neg_data*) ; 
 scalar_t__ nsec3_get_params (struct ub_packed_rrset_key*,int /*<<< orphan*/ ,int*,size_t*,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ query_dname_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbtree_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sec_status_secure ; 
 scalar_t__ sec_status_unchecked ; 
 int /*<<< orphan*/  wipeout (struct val_neg_cache*,struct val_neg_zone*,struct val_neg_data*,struct ub_packed_rrset_key*) ; 

void neg_insert_data(struct val_neg_cache* neg, 
	struct val_neg_zone* zone, struct ub_packed_rrset_key* nsec)
{
	struct packed_rrset_data* d;
	struct val_neg_data* parent;
	struct val_neg_data* el;
	uint8_t* nm = nsec->rk.dname;
	size_t nm_len = nsec->rk.dname_len;
	int labs = dname_count_labels(nsec->rk.dname);

	d = (struct packed_rrset_data*)nsec->entry.data;
	if( !(d->security == sec_status_secure ||
		(d->security == sec_status_unchecked && d->rrsig_count > 0)))
		return;
	log_nametypeclass(VERB_ALGO, "negcache rr", 
		nsec->rk.dname, ntohs(nsec->rk.type), 
		ntohs(nsec->rk.rrset_class));

	/* find closest enclosing parent data that (still) exists */
	parent = neg_closest_data_parent(zone, nm, nm_len, labs);
	if(parent && query_dname_compare(parent->name, nm) == 0) {
		/* perfect match already exists */
		log_assert(parent->count > 0);
		el = parent;
	} else { 
		struct val_neg_data* p, *np;

		/* create subtree for perfect match */
		/* if parent exists, it is in use */
		log_assert(!parent || parent->count > 0);

		el = neg_data_chain(nm, nm_len, labs, parent);
		if(!el) {
			log_err("out of memory inserting NSEC negative cache");
			return;
		}
		el->in_use = 0; /* set on below */

		/* insert the list of zones into the tree */
		p = el;
		while(p) {
			np = p->parent;
			/* mem use */
			neg->use += sizeof(struct val_neg_data) + p->len;
			/* insert in tree */
			p->zone = zone;
			(void)rbtree_insert(&zone->tree, &p->node);
			/* last one needs proper parent pointer */
			if(np == NULL)
				p->parent = parent;
			p = np;
		}
	}

	if(!el->in_use) {
		struct val_neg_data* p;

		el->in_use = 1;
		/* increase usage count of all parents */
		for(p=el; p; p = p->parent) {
			p->count++;
		}

		neg_lru_front(neg, el);
	} else {
		/* in use, bring to front, lru */
		neg_lru_touch(neg, el);
	}

	/* if nsec3 store last used parameters */
	if(ntohs(nsec->rk.type) == LDNS_RR_TYPE_NSEC3) {
		int h;
		uint8_t* s;
		size_t slen, it;
		if(nsec3_get_params(nsec, 0, &h, &it, &s, &slen) &&
			it <= neg->nsec3_max_iter &&
			(h != zone->nsec3_hash || it != zone->nsec3_iter ||
			slen != zone->nsec3_saltlen || 
			memcmp(zone->nsec3_salt, s, slen) != 0)) {

			if(slen > 0) {
				uint8_t* sa = memdup(s, slen);
				if(sa) {
					free(zone->nsec3_salt);
					zone->nsec3_salt = sa;
					zone->nsec3_saltlen = slen;
					zone->nsec3_iter = it;
					zone->nsec3_hash = h;
				}
			} else {
				free(zone->nsec3_salt);
				zone->nsec3_salt = NULL;
				zone->nsec3_saltlen = 0;
				zone->nsec3_iter = it;
				zone->nsec3_hash = h;
			}
		}
	}

	/* wipe out the cache items between NSEC start and end */
	wipeout(neg, zone, el, nsec);
}