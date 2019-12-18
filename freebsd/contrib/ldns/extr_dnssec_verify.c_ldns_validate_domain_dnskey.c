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
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  ldns_time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_validate_domain_dnskey_time (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

ldns_rr_list *
ldns_validate_domain_dnskey(const ldns_resolver * res,
					   const ldns_rdf * domain,
					   const ldns_rr_list * keys)
{
	return ldns_validate_domain_dnskey_time(
			res, domain, keys, ldns_time(NULL));
}