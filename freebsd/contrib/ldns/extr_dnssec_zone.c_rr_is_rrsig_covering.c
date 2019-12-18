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
typedef  scalar_t__ ldns_rr_type ;
typedef  int /*<<< orphan*/  ldns_rr ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 scalar_t__ ldns_rdf2rr_type (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rr_rrsig_typecovered (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
rr_is_rrsig_covering(ldns_rr* rr, ldns_rr_type t)
{
	return     ldns_rr_get_type(rr) == LDNS_RR_TYPE_RRSIG
		&& ldns_rdf2rr_type(ldns_rr_rrsig_typecovered(rr)) == t;
}