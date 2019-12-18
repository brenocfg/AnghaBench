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
struct val_env {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; TYPE_1__ entry; } ;
struct trust_anchor {int dummy; } ;
struct packed_rrset_data {size_t count; scalar_t__* rr_len; scalar_t__* rr_data; } ;
struct module_qstate {int dummy; } ;
struct module_env {int dummy; } ;
struct autr_ta {int /*<<< orphan*/  revoked; int /*<<< orphan*/  dname_len; int /*<<< orphan*/  rr_len; int /*<<< orphan*/  rr; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int dnskey_calc_keytag (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  do_revoked (struct module_env*,struct autr_ta*,int*) ; 
 int /*<<< orphan*/  find_key (struct trust_anchor*,scalar_t__,scalar_t__,scalar_t__,struct autr_ta**) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rr_is_dnskey_revoked (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rr_is_dnskey_sep (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ rr_is_selfsigned_revoked (struct module_env*,struct val_env*,struct ub_packed_rrset_key*,size_t,struct module_qstate*) ; 
 int /*<<< orphan*/  seen_revoked_trustanchor (struct autr_ta*,int) ; 
 int sldns_calc_keytag_raw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wirerr_get_rdata (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wirerr_get_rdatalen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose_key (struct autr_ta*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
check_contains_revoked(struct module_env* env, struct val_env* ve,
	struct trust_anchor* tp, struct ub_packed_rrset_key* dnskey_rrset,
	int* changed, struct module_qstate* qstate)
{
	struct packed_rrset_data* dd = (struct packed_rrset_data*)
		dnskey_rrset->entry.data;
	size_t i;
	log_assert(ntohs(dnskey_rrset->rk.type) == LDNS_RR_TYPE_DNSKEY);
	for(i=0; i<dd->count; i++) {
		struct autr_ta* ta = NULL;
		if(!rr_is_dnskey_sep(ntohs(dnskey_rrset->rk.type),
			dd->rr_data[i]+2, dd->rr_len[i]-2) ||
			!rr_is_dnskey_revoked(ntohs(dnskey_rrset->rk.type),
			dd->rr_data[i]+2, dd->rr_len[i]-2))
			continue; /* not a revoked KSK */
		if(!find_key(tp, ntohs(dnskey_rrset->rk.type),
			dd->rr_data[i]+2, dd->rr_len[i]-2, &ta)) {
			log_err("malloc failure");
			continue; /* malloc fail in compare*/
		}
		if(!ta)
			continue; /* key not found */
		if(rr_is_selfsigned_revoked(env, ve, dnskey_rrset, i, qstate)) {
			/* checked if there is an rrsig signed by this key. */
			/* same keytag, but stored can be revoked already, so 
			 * compare keytags, with +0 or +128(REVOKE flag) */
			log_assert(dnskey_calc_keytag(dnskey_rrset, i)-128 ==
				sldns_calc_keytag_raw(sldns_wirerr_get_rdata(
				ta->rr, ta->rr_len, ta->dname_len),
				sldns_wirerr_get_rdatalen(ta->rr, ta->rr_len,
				ta->dname_len)) ||
				dnskey_calc_keytag(dnskey_rrset, i) ==
				sldns_calc_keytag_raw(sldns_wirerr_get_rdata(
				ta->rr, ta->rr_len, ta->dname_len),
				sldns_wirerr_get_rdatalen(ta->rr, ta->rr_len,
				ta->dname_len))); /* checks conversion*/
			verbose_key(ta, VERB_ALGO, "is self-signed revoked");
			if(!ta->revoked) 
				*changed = 1;
			seen_revoked_trustanchor(ta, 1);
			do_revoked(env, ta, changed);
		}
	}
}