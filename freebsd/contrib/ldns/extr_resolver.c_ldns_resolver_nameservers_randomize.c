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
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  ldns_resolver ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t ldns_get_random () ; 
 size_t ldns_resolver_nameserver_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** ldns_resolver_nameservers (int /*<<< orphan*/ *) ; 
 size_t* ldns_resolver_rtt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_set_nameservers (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

void
ldns_resolver_nameservers_randomize(ldns_resolver *r)
{
	uint16_t i, j;
	ldns_rdf **ns, *tmpns;
	size_t *rtt, tmprtt;

	/* should I check for ldns_resolver_random?? */
	assert(r != NULL);

	ns = ldns_resolver_nameservers(r);
	rtt = ldns_resolver_rtt(r);
	for (i = 0; i < ldns_resolver_nameserver_count(r); i++) {
		j = ldns_get_random() % ldns_resolver_nameserver_count(r);
		tmpns = ns[i];
		ns[i] = ns[j];
		ns[j] = tmpns;
		tmprtt = rtt[i];
		rtt[i] = rtt[j];
		rtt[j] = tmprtt;
	}
	ldns_resolver_set_nameservers(r, ns);
}