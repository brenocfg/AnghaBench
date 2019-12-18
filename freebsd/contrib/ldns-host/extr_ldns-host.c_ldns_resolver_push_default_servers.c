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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_push_nameserver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_str2rdf_a (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  ldns_str2rdf_aaaa (int /*<<< orphan*/ **,char*) ; 

__attribute__((used)) static ldns_status
ldns_resolver_push_default_servers(ldns_resolver *res) {
    ldns_status status;
    ldns_rdf *addr;

    if ((status = ldns_str2rdf_a(&addr, "127.0.0.1")) != LDNS_STATUS_OK ||
        (status = ldns_resolver_push_nameserver(res, addr)) != LDNS_STATUS_OK)
        return ldns_rdf_deep_free(addr), status;
    ldns_rdf_deep_free(addr);
    if ((status = ldns_str2rdf_aaaa(&addr, "::1")) != LDNS_STATUS_OK ||
        (status = ldns_resolver_push_nameserver(res, addr)) != LDNS_STATUS_OK)
        return ldns_rdf_deep_free(addr), status;
    ldns_rdf_deep_free(addr);
    return LDNS_STATUS_OK;
}