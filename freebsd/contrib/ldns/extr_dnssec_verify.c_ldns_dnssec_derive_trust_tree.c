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
typedef  int /*<<< orphan*/  ldns_dnssec_trust_tree ;
typedef  int /*<<< orphan*/  ldns_dnssec_data_chain ;

/* Variables and functions */
 int /*<<< orphan*/ * ldns_dnssec_derive_trust_tree_time (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_time (int /*<<< orphan*/ *) ; 

ldns_dnssec_trust_tree *
ldns_dnssec_derive_trust_tree(ldns_dnssec_data_chain *data_chain, ldns_rr *rr)
{
	return ldns_dnssec_derive_trust_tree_time(data_chain, rr, ldns_time(NULL));
}