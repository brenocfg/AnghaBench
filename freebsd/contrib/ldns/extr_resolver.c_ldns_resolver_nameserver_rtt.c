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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 size_t ldns_resolver_nameserver_count (int /*<<< orphan*/  const*) ; 
 size_t* ldns_resolver_rtt (int /*<<< orphan*/  const*) ; 

size_t
ldns_resolver_nameserver_rtt(const ldns_resolver *r, size_t pos)
{
	size_t *rtt;

	assert(r != NULL);

	rtt = ldns_resolver_rtt(r);

	if (pos >= ldns_resolver_nameserver_count(r)) {
		/* error ?*/
		return 0;
	} else {
		return rtt[pos];
	}

}