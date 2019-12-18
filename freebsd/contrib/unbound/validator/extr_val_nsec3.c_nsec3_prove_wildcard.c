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
struct val_env {int dummy; } ;
struct ub_packed_rrset_key {int dummy; } ;
struct query_info {int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct nsec3_filter {int /*<<< orphan*/  zone; } ;
struct module_env {int dummy; } ;
struct key_entry_key {int dummy; } ;
struct ce_response {size_t ce_len; int /*<<< orphan*/  nc_rr; scalar_t__ nc_rrset; int /*<<< orphan*/ * ce; } ;
typedef  int /*<<< orphan*/  rbtree_type ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;
typedef  int /*<<< orphan*/  ce ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  filter_init (struct nsec3_filter*,struct ub_packed_rrset_key**,size_t,struct query_info*) ; 
 int /*<<< orphan*/  find_covering_nsec3 (struct module_env*,struct nsec3_filter*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_entry_isgood (struct key_entry_key*) ; 
 int /*<<< orphan*/  memset (struct ce_response*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next_closer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*) ; 
 scalar_t__ nsec3_has_optout (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsec3_hash_cmp ; 
 scalar_t__ nsec3_iteration_count_high (struct val_env*,struct nsec3_filter*,struct key_entry_key*) ; 
 int /*<<< orphan*/  rbtree_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sec_status_bogus ; 
 int sec_status_insecure ; 
 int sec_status_secure ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

enum sec_status
nsec3_prove_wildcard(struct module_env* env, struct val_env* ve,
        struct ub_packed_rrset_key** list, size_t num,
	struct query_info* qinfo, struct key_entry_key* kkey, uint8_t* wc)
{
	rbtree_type ct;
	struct nsec3_filter flt;
	struct ce_response ce;
	uint8_t* nc;
	size_t nc_len;
	size_t wclen;
	(void)dname_count_size_labels(wc, &wclen);

	if(!list || num == 0 || !kkey || !key_entry_isgood(kkey))
		return sec_status_bogus; /* no valid NSEC3s, bogus */
	rbtree_init(&ct, &nsec3_hash_cmp); /* init names-to-hash cache */
	filter_init(&flt, list, num, qinfo); /* init RR iterator */
	if(!flt.zone)
		return sec_status_bogus; /* no RRs */
	if(nsec3_iteration_count_high(ve, &flt, kkey))
		return sec_status_insecure; /* iteration count too high */

	/* We know what the (purported) closest encloser is by just 
	 * looking at the supposed generating wildcard. 
	 * The *. has already been removed from the wc name.
	 */
	memset(&ce, 0, sizeof(ce));
	ce.ce = wc;
	ce.ce_len = wclen;

	/* Now we still need to prove that the original data did not exist.
	 * Otherwise, we need to show that the next closer name is covered. */
	next_closer(qinfo->qname, qinfo->qname_len, ce.ce, &nc, &nc_len);
	if(!find_covering_nsec3(env, &flt, &ct, nc, nc_len, 
		&ce.nc_rrset, &ce.nc_rr)) {
		verbose(VERB_ALGO, "proveWildcard: did not find a covering "
			"NSEC3 that covered the next closer name.");
		return sec_status_bogus;
	}
	if(ce.nc_rrset && nsec3_has_optout(ce.nc_rrset, ce.nc_rr)) {
		verbose(VERB_ALGO, "proveWildcard: NSEC3 optout");
		return sec_status_insecure;
	}
	return sec_status_secure;
}