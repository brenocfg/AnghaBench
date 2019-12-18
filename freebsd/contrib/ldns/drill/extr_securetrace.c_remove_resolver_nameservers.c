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
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_resolver_pop_nameserver (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
remove_resolver_nameservers(ldns_resolver *res)
{
	ldns_rdf *pop;
	
	/* remove the old nameserver from the resolver */
	while((pop = ldns_resolver_pop_nameserver(res))) {
		ldns_rdf_deep_free(pop);
	}

}