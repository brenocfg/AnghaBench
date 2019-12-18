#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* _rdata_fields; } ;
typedef  TYPE_1__ ldns_rr ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (scalar_t__) ; 
 scalar_t__ ldns_rr_owner (TYPE_1__*) ; 
 size_t ldns_rr_rd_count (TYPE_1__*) ; 
 scalar_t__ ldns_rr_rdf (TYPE_1__*,size_t) ; 

void
ldns_rr_free(ldns_rr *rr)
{
	size_t i;
	if (rr) {
		if (ldns_rr_owner(rr)) {
			ldns_rdf_deep_free(ldns_rr_owner(rr));
		}
		for (i = 0; i < ldns_rr_rd_count(rr); i++) {
			ldns_rdf_deep_free(ldns_rr_rdf(rr, i));
		}
		LDNS_FREE(rr->_rdata_fields);
		LDNS_FREE(rr);
	}
}