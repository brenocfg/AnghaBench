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
struct val_env {int dummy; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct packed_rrset_data {size_t count; } ;
struct module_env {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ dnskey_calc_keytag (struct ub_packed_rrset_key*,size_t) ; 
 scalar_t__ dnskey_get_algo (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  ds_digest_algo_is_supported (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  ds_digest_match_dnskey (struct module_env*,struct ub_packed_rrset_key*,size_t,struct ub_packed_rrset_key*,size_t) ; 
 int ds_get_digest_algo (struct ub_packed_rrset_key*,size_t) ; 
 scalar_t__ ds_get_key_algo (struct ub_packed_rrset_key*,size_t) ; 
 scalar_t__ ds_get_keytag (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  ds_key_algo_is_supported (struct ub_packed_rrset_key*,size_t) ; 
 int val_favorite_ds_algo (struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
key_matches_a_ds(struct module_env* env, struct val_env* ve,
	struct ub_packed_rrset_key* dnskey_rrset, size_t key_idx,
	struct ub_packed_rrset_key* ds_rrset)
{
	struct packed_rrset_data* dd = (struct packed_rrset_data*)
	                ds_rrset->entry.data;
	size_t ds_idx, num = dd->count;
	int d = val_favorite_ds_algo(ds_rrset);
	char* reason = "";
	for(ds_idx=0; ds_idx<num; ds_idx++) {
		if(!ds_digest_algo_is_supported(ds_rrset, ds_idx) ||
			!ds_key_algo_is_supported(ds_rrset, ds_idx) ||
			ds_get_digest_algo(ds_rrset, ds_idx) != d)
			continue;
		if(ds_get_key_algo(ds_rrset, ds_idx)
		   != dnskey_get_algo(dnskey_rrset, key_idx)
		   || dnskey_calc_keytag(dnskey_rrset, key_idx)
		   != ds_get_keytag(ds_rrset, ds_idx)) {
			continue;
		}
		if(!ds_digest_match_dnskey(env, dnskey_rrset, key_idx,
			ds_rrset, ds_idx)) {
			verbose(VERB_ALGO, "DS match attempt failed");
			continue;
		}
		/* match of hash is sufficient for bootstrap of trust point */
		(void)reason;
		(void)ve;
		return 1;
		/* no need to check RRSIG, DS hash already matched with source
		if(dnskey_verify_rrset(env, ve, dnskey_rrset, 
			dnskey_rrset, key_idx, &reason) == sec_status_secure) {
			return 1;
		} else {
			verbose(VERB_ALGO, "DS match failed because the key "
				"does not verify the keyset: %s", reason);
		}
		*/
	}
	return 0;
}