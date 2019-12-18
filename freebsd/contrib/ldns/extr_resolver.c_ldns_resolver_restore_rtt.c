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
 int /*<<< orphan*/  LDNS_FREE (size_t*) ; 
 size_t* ldns_resolver_rtt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_resolver_set_rtt (int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static void
ldns_resolver_restore_rtt(ldns_resolver *r, size_t *old_rtt)
{
	size_t *cur_rtt = ldns_resolver_rtt(r);

	if (cur_rtt) {
		LDNS_FREE(cur_rtt);
	}
	ldns_resolver_set_rtt(r, old_rtt);
}