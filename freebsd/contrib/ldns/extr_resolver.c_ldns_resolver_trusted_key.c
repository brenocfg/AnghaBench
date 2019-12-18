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
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;

/* Variables and functions */
 int /*<<< orphan*/ * ldns_resolver_dnssec_anchors (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rr_list_contains_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 

bool
ldns_resolver_trusted_key(const ldns_resolver *r, ldns_rr_list * keys, ldns_rr_list * trusted_keys)
{
  size_t i;
  bool result = false;

  ldns_rr_list * trust_anchors;
  ldns_rr * cur_rr;

  if (!r || !keys) { return false; }

  trust_anchors = ldns_resolver_dnssec_anchors(r);

  if (!trust_anchors) { return false; }

  for (i = 0; i < ldns_rr_list_rr_count(keys); i++) {

    cur_rr = ldns_rr_list_rr(keys, i);
    if (ldns_rr_list_contains_rr(trust_anchors, cur_rr)) {
      if (trusted_keys) { ldns_rr_list_push_rr(trusted_keys, cur_rr); }
      result = true;
    }
  }

  return result;
}