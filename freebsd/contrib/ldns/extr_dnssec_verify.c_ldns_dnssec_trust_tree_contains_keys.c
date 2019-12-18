#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
struct TYPE_3__ {size_t parent_count; scalar_t__* parent_status; scalar_t__ rr; struct TYPE_3__** parents; } ;
typedef  TYPE_1__ ldns_dnssec_trust_tree ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_STATUS_CRYPTO_NO_DNSKEY ; 
 scalar_t__ LDNS_STATUS_DNSSEC_EXISTENCE_DENIED ; 
 scalar_t__ LDNS_STATUS_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int ldns_rr_compare_ds (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rr_get_type (scalar_t__) ; 
 int /*<<< orphan*/  ldns_rr_list_rr (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_rr_list_rr_count (int /*<<< orphan*/ *) ; 

ldns_status
ldns_dnssec_trust_tree_contains_keys(ldns_dnssec_trust_tree *tree,
							  ldns_rr_list *trusted_keys)
{
	size_t i;
	ldns_status result = LDNS_STATUS_CRYPTO_NO_DNSKEY;
	bool equal;
	ldns_status parent_result;
	
	if (tree && trusted_keys && ldns_rr_list_rr_count(trusted_keys) > 0)
		{ if (tree->rr) {
				for (i = 0; i < ldns_rr_list_rr_count(trusted_keys); i++) {
					equal = ldns_rr_compare_ds(
							  tree->rr,
							  ldns_rr_list_rr(trusted_keys, i));
					if (equal) {
						result = LDNS_STATUS_OK;
						return result;
					}
				}
			}
			for (i = 0; i < tree->parent_count; i++) {
				parent_result =
					ldns_dnssec_trust_tree_contains_keys(tree->parents[i],
												  trusted_keys);
				if (parent_result != LDNS_STATUS_CRYPTO_NO_DNSKEY) {
					if (tree->parent_status[i] != LDNS_STATUS_OK) {
						result = tree->parent_status[i];
					} else {
						if (tree->rr &&
						    ldns_rr_get_type(tree->rr)
						    == LDNS_RR_TYPE_NSEC &&
						    parent_result == LDNS_STATUS_OK
						    ) {
							result =
								LDNS_STATUS_DNSSEC_EXISTENCE_DENIED;
						} else {
							result = parent_result;
						}
					}
				}
			}
		} else {
		result = LDNS_STATUS_ERR;
	}
	
	return result;
}