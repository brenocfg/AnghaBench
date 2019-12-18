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
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  die (int,char*) ; 
 int /*<<< orphan*/ * ldns_rdf_new_addr_frm_str (char const*) ; 
 scalar_t__ ldns_resolver_push_nameserver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_remove_nameservers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolver_set_nameserver_hostname (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
resolver_set_nameserver_str(ldns_resolver *res, const char *server) {
    ldns_rdf *addr;

    ldns_resolver_remove_nameservers(res);
    addr = ldns_rdf_new_addr_frm_str(server);
    if (addr) {
        if (ldns_resolver_push_nameserver(res, addr) != LDNS_STATUS_OK)
            die(1, "couldn't push a nameserver address");
    } else
        resolver_set_nameserver_hostname(res, server);
}