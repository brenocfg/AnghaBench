#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_rr ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ldns_dnssec_name ;

/* Variables and functions */
 scalar_t__ LDNS_STATUS_OK ; 
 scalar_t__ ldns_dnssec_name_add_rr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_dnssec_name_free (TYPE_1__*) ; 
 TYPE_1__* ldns_dnssec_name_new () ; 
 int /*<<< orphan*/  ldns_rr_owner (int /*<<< orphan*/ *) ; 

ldns_dnssec_name *
ldns_dnssec_name_new_frm_rr(ldns_rr *rr)
{
	ldns_dnssec_name *new_name = ldns_dnssec_name_new();

	new_name->name = ldns_rr_owner(rr);
	if(ldns_dnssec_name_add_rr(new_name, rr) != LDNS_STATUS_OK) {
		ldns_dnssec_name_free(new_name);
		return NULL;
	}

	return new_name;
}