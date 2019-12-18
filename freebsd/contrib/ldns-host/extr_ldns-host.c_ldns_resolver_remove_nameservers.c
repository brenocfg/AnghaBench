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

/* Variables and functions */
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ ) ; 
 scalar_t__ ldns_resolver_nameserver_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_pop_nameserver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ldns_resolver_remove_nameservers(ldns_resolver *res) {
    while (ldns_resolver_nameserver_count(res) > 0)
        ldns_rdf_deep_free(ldns_resolver_pop_nameserver(res));
}