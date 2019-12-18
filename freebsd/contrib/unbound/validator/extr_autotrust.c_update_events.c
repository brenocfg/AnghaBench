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
typedef  int /*<<< orphan*/  uint32_t ;
struct val_env {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; TYPE_1__ entry; } ;
struct trust_anchor {scalar_t__ ds_rrset; int /*<<< orphan*/  dclass; int /*<<< orphan*/  name; } ;
struct packed_rrset_data {size_t count; scalar_t__* rr_len; scalar_t__* rr_data; scalar_t__* rr_ttl; } ;
struct module_env {int dummy; } ;
struct autr_ta {int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTR_STATE_VALID ; 
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  VERB_DETAIL ; 
 struct autr_ta* add_key (struct trust_anchor*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  dnskey_algo_is_supported (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  find_key (struct trust_anchor*,scalar_t__,scalar_t__,scalar_t__,struct autr_ta**) ; 
 int /*<<< orphan*/  init_events (struct trust_anchor*) ; 
 scalar_t__ key_matches_a_ds (struct module_env*,struct val_env*,struct ub_packed_rrset_key*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  key_ttl (struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min_expiry (struct module_env*,struct packed_rrset_data*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ rr_is_dnskey_revoked (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rr_is_dnskey_sep (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  seen_trustanchor (struct autr_ta*,int) ; 
 int /*<<< orphan*/  set_tp_times (struct trust_anchor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  verbose_key (struct autr_ta*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
update_events(struct module_env* env, struct val_env* ve, 
	struct trust_anchor* tp, struct ub_packed_rrset_key* dnskey_rrset, 
	int* changed)
{
	struct packed_rrset_data* dd = (struct packed_rrset_data*)
		dnskey_rrset->entry.data;
	size_t i;
	log_assert(ntohs(dnskey_rrset->rk.type) == LDNS_RR_TYPE_DNSKEY);
	init_events(tp);
	for(i=0; i<dd->count; i++) {
		struct autr_ta* ta = NULL;
		if(!rr_is_dnskey_sep(ntohs(dnskey_rrset->rk.type),
			dd->rr_data[i]+2, dd->rr_len[i]-2))
			continue;
		if(rr_is_dnskey_revoked(ntohs(dnskey_rrset->rk.type),
			dd->rr_data[i]+2, dd->rr_len[i]-2)) {
			/* self-signed revoked keys already detected before,
			 * other revoked keys are not 'added' again */
			continue;
		}
		/* is a key of this type supported?. Note rr_list and
		 * packed_rrset are in the same order. */
		if(!dnskey_algo_is_supported(dnskey_rrset, i)) {
			/* skip unknown algorithm key, it is useless to us */
			log_nametypeclass(VERB_DETAIL, "trust point has "
				"unsupported algorithm at", 
				tp->name, LDNS_RR_TYPE_DNSKEY, tp->dclass);
			continue;
		}

		/* is it new? if revocation bit set, find the unrevoked key */
		if(!find_key(tp, ntohs(dnskey_rrset->rk.type),
			dd->rr_data[i]+2, dd->rr_len[i]-2, &ta)) {
			return 0;
		}
		if(!ta) {
			ta = add_key(tp, (uint32_t)dd->rr_ttl[i],
				dd->rr_data[i]+2, dd->rr_len[i]-2);
			*changed = 1;
			/* first time seen, do we have DSes? if match: VALID */
			if(ta && tp->ds_rrset && key_matches_a_ds(env, ve,
				dnskey_rrset, i, tp->ds_rrset)) {
				verbose_key(ta, VERB_ALGO, "verified by DS");
				ta->s = AUTR_STATE_VALID;
			}
		}
		if(!ta) {
			return 0;
		}
		seen_trustanchor(ta, 1);
		verbose_key(ta, VERB_ALGO, "in DNS response");
	}
	set_tp_times(tp, min_expiry(env, dd), key_ttl(dnskey_rrset), changed);
	return 1;
}