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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  const ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_NO_TRUSTED_DNSKEY ; 
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_NO_TRUSTED_DS ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  const* ldns_dname_left_chop (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/  const*) ; 
 scalar_t__ ldns_rdf_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_list_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_validate_domain_dnskey_time (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ldns_validate_domain_ds_time (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ldns_rr_list *
ldns_fetch_valid_domain_keys_time(const ldns_resolver *res,
                             const ldns_rdf *domain,
                             const ldns_rr_list *keys,
			     time_t check_time,
                             ldns_status *status)
{
	ldns_rr_list * trusted_keys = NULL;
	ldns_rr_list * ds_keys = NULL;
	ldns_rdf * prev_parent_domain;
	ldns_rdf *      parent_domain;
	ldns_rr_list * parent_keys = NULL;

	if (res && domain && keys) {

		if ((trusted_keys = ldns_validate_domain_dnskey_time(res,
                                         domain, keys, check_time))) {
			*status = LDNS_STATUS_OK;
		} else {
			/* No trusted keys in this domain, we'll have to find some in the parent domain */
			*status = LDNS_STATUS_CRYPTO_NO_TRUSTED_DNSKEY;

			parent_domain = ldns_dname_left_chop(domain);
			while (parent_domain && /* Fail if we are at the root*/
					ldns_rdf_size(parent_domain) > 0) {
	
				if ((parent_keys = 
					ldns_fetch_valid_domain_keys_time(res,
					     parent_domain,
					     keys,
					     check_time,
					     status))) {
					/* Check DS records */
					if ((ds_keys =
						ldns_validate_domain_ds_time(res,
						     domain,
						     parent_keys,
						     check_time))) {
						trusted_keys =
						ldns_fetch_valid_domain_keys_time(
								res, 
								domain, 
								ds_keys, 
								check_time,
								status);
						ldns_rr_list_deep_free(ds_keys);
					} else {
						/* No valid DS at the parent -- fail */
						*status = LDNS_STATUS_CRYPTO_NO_TRUSTED_DS ;
					}
					ldns_rr_list_deep_free(parent_keys);
					break;
				} else {
					parent_domain = ldns_dname_left_chop((
						prev_parent_domain 
							= parent_domain
						));
					ldns_rdf_deep_free(prev_parent_domain);
				}
			}
			if (parent_domain) {
				ldns_rdf_deep_free(parent_domain);
			}
		}
	}
	return trusted_keys;
}