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
struct ip_fw {int refcnt; int /*<<< orphan*/  cntr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int /*<<< orphan*/  V_ipfw_cntr_zone ; 
 int /*<<< orphan*/  free (struct ip_fw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree_pcpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ipfw_free_rule(struct ip_fw *rule)
{

	/*
	 * We don't release refcnt here, since this function
	 * can be called without any locks held. The caller
	 * must release reference under IPFW_UH_WLOCK, and then
	 * call this function if refcount becomes 1.
	 */
	if (rule->refcnt > 1)
		return;
	uma_zfree_pcpu(V_ipfw_cntr_zone, rule->cntr);
	free(rule, M_IPFW);
}