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
 size_t ldns_resolver_nameserver_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_set_nameserver_count (int /*<<< orphan*/ *,size_t) ; 

void
ldns_resolver_incr_nameserver_count(ldns_resolver *r)
{
	size_t c;

	c = ldns_resolver_nameserver_count(r);
	ldns_resolver_set_nameserver_count(r, ++c);
}