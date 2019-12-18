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

/* Variables and functions */
 int /*<<< orphan*/  ldns_rdf2native_int8 (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_rdf_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rdf_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_rr_dnskey_algorithm (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rr_dnskey_key (int /*<<< orphan*/  const*) ; 
 size_t ldns_rr_dnskey_key_size_raw (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

size_t 
ldns_rr_dnskey_key_size(const ldns_rr *key) 
{
	if (!key || !ldns_rr_dnskey_key(key) 
			|| !ldns_rr_dnskey_algorithm(key)) {
		return 0;
	}
	return ldns_rr_dnskey_key_size_raw((unsigned char*)ldns_rdf_data(ldns_rr_dnskey_key(key)),
	                                   ldns_rdf_size(ldns_rr_dnskey_key(key)),
	                                   ldns_rdf2native_int8(ldns_rr_dnskey_algorithm(key))
	                                  );
}