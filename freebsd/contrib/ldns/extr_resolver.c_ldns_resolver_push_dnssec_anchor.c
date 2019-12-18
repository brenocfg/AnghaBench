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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_DNSKEY ; 
 scalar_t__ LDNS_RR_TYPE_DS ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/ * ldns_resolver_dnssec_anchors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_set_dnssec_anchors (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_clone (int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_list_new () ; 
 scalar_t__ ldns_rr_list_push_rr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ldns_status
ldns_resolver_push_dnssec_anchor(ldns_resolver *r, ldns_rr *rr)
{
  ldns_rr_list * trust_anchors;

  if ((!rr) || (ldns_rr_get_type(rr) != LDNS_RR_TYPE_DNSKEY &&
                ldns_rr_get_type(rr) != LDNS_RR_TYPE_DS)) {

    return LDNS_STATUS_ERR;
  }

  if (!(trust_anchors = ldns_resolver_dnssec_anchors(r))) { /* Initialize */
    trust_anchors = ldns_rr_list_new();
    ldns_resolver_set_dnssec_anchors(r, trust_anchors);
  }

  return (ldns_rr_list_push_rr(trust_anchors, ldns_rr_clone(rr))) ? LDNS_STATUS_OK : LDNS_STATUS_ERR;
}