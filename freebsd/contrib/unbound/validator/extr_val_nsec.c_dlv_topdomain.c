#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;

/* Variables and functions */
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dname_get_shared_topdomain (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dname_remove_labels (int /*<<< orphan*/ **,size_t*,int) ; 

__attribute__((used)) static void
dlv_topdomain(struct ub_packed_rrset_key* nsec, uint8_t* qname,
	uint8_t** nm, size_t* nm_len)
{
	/* make sure reply is part of nm */
	/* take shared topdomain with left of NSEC. */

	/* because, if empty nonterminal, then right is subdomain of qname.
	 * and any shared topdomain would be empty nonterminals.
	 * 
	 * If nxdomain, then the right is bigger, and could have an 
	 * interesting shared topdomain, but if it does have one, it is
	 * an empty nonterminal. An empty nonterminal shared with the left
	 * one. */
	int n;
	uint8_t* common = dname_get_shared_topdomain(qname, nsec->rk.dname);
	n = dname_count_labels(*nm) - dname_count_labels(common);
	dname_remove_labels(nm, nm_len, n);
}