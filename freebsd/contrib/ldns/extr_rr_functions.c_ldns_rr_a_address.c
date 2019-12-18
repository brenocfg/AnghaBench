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
typedef  int /*<<< orphan*/  ldns_rr ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ldns_rr_rdf (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

ldns_rdf *
ldns_rr_a_address(const ldns_rr *r)
{
	/* 2 types to check, cannot use the macro */
	if (!r || (ldns_rr_get_type(r) != LDNS_RR_TYPE_A &&
			ldns_rr_get_type(r) != LDNS_RR_TYPE_AAAA)) {
		return NULL;
	}
	return ldns_rr_rdf(r, 0);
}