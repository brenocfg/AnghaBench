#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_8__ {scalar_t__ type; TYPE_1__* signatures; TYPE_2__* rrs; } ;
typedef  TYPE_3__ ldns_dnssec_rrsets ;
struct TYPE_7__ {int /*<<< orphan*/ * rr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * rr; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 void* ldns_dnssec_rrs_new () ; 
 TYPE_3__* ldns_dnssec_rrsets_new () ; 
 scalar_t__ ldns_rdf2rr_type (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_typecovered (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ldns_dnssec_rrsets *
ldns_dnssec_rrsets_new_frm_rr(ldns_rr *rr)
{
	ldns_dnssec_rrsets *new_rrsets;
	ldns_rr_type rr_type;
	bool rrsig;

	new_rrsets = ldns_dnssec_rrsets_new();
	rr_type = ldns_rr_get_type(rr);
	if (rr_type == LDNS_RR_TYPE_RRSIG) {
		rrsig = true;
		rr_type = ldns_rdf2rr_type(ldns_rr_rrsig_typecovered(rr));
	} else {
		rrsig = false;
	}
	if (!rrsig) {
		new_rrsets->rrs = ldns_dnssec_rrs_new();
		new_rrsets->rrs->rr = rr;
	} else {
		new_rrsets->signatures = ldns_dnssec_rrs_new();
		new_rrsets->signatures->rr = rr;
	}
	new_rrsets->type = rr_type;
	return new_rrsets;
}