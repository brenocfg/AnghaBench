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
struct ip_fw_chain {int dummy; } ;
struct ip_fw {int refcnt; int /*<<< orphan*/  cntr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  V_ipfw_cntr_zone ; 
 struct ip_fw* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uma_zalloc_pcpu (int /*<<< orphan*/ ,int) ; 

struct ip_fw *
ipfw_alloc_rule(struct ip_fw_chain *chain, size_t rulesize)
{
	struct ip_fw *rule;

	rule = malloc(rulesize, M_IPFW, M_WAITOK | M_ZERO);
	rule->cntr = uma_zalloc_pcpu(V_ipfw_cntr_zone, M_WAITOK | M_ZERO);
	rule->refcnt = 1;

	return (rule);
}