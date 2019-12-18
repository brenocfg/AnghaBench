#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_4__ {struct TYPE_4__* next; int /*<<< orphan*/ * rr; } ;
typedef  TYPE_1__ ldns_dnssec_rrs ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 TYPE_1__* ldns_dnssec_rrs_new () ; 
 int ldns_rr_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ldns_status
ldns_dnssec_rrs_add_rr(ldns_dnssec_rrs *rrs, ldns_rr *rr)
{
	int cmp;
	ldns_dnssec_rrs *new_rrs;
	if (!rrs || !rr) {
		return LDNS_STATUS_ERR;
	}

	/* this could be done more efficiently; name and type should already
	   be equal */
	cmp = ldns_rr_compare(rrs->rr, rr);
	if (cmp < 0) {
		if (rrs->next) {
			return ldns_dnssec_rrs_add_rr(rrs->next, rr);
		} else {
			new_rrs = ldns_dnssec_rrs_new();
			new_rrs->rr = rr;
			rrs->next = new_rrs;
		}
	} else if (cmp > 0) {
		/* put the current old rr in the new next, put the new
		   rr in the current container */
		new_rrs = ldns_dnssec_rrs_new();
		new_rrs->rr = rrs->rr;
		new_rrs->next = rrs->next;
		rrs->rr = rr;
		rrs->next = new_rrs;
	}
	/* Silently ignore equal rr's */
	return LDNS_STATUS_OK;
}