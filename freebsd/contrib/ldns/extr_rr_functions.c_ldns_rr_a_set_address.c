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
 int /*<<< orphan*/  LDNS_FREE (int /*<<< orphan*/ *) ; 
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rr_set_rdf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool
ldns_rr_a_set_address(ldns_rr *r, ldns_rdf *f)
{
	/* 2 types to check, cannot use the macro... */
	ldns_rdf *pop;
	if (!r || (ldns_rr_get_type(r) != LDNS_RR_TYPE_A &&
			ldns_rr_get_type(r) != LDNS_RR_TYPE_AAAA)) {
		return false;
	}
	pop = ldns_rr_set_rdf(r, f, 0);
	if (pop) {
		LDNS_FREE(pop);
		return true;
	} else {
		return false;
	}
}