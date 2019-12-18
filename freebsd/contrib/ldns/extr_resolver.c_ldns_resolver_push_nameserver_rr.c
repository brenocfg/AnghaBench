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
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  ldns_resolver_push_nameserver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

ldns_status
ldns_resolver_push_nameserver_rr(ldns_resolver *r, const ldns_rr *rr)
{
	ldns_rdf *address;
	if ((!rr) || (ldns_rr_get_type(rr) != LDNS_RR_TYPE_A &&
			ldns_rr_get_type(rr) != LDNS_RR_TYPE_AAAA)) {
		return LDNS_STATUS_ERR;
	}
	address = ldns_rr_rdf(rr, 0); /* extract the ip number */
	if (address) {
		return ldns_resolver_push_nameserver(r, address);
	} else {
		return LDNS_STATUS_ERR;
	}
}