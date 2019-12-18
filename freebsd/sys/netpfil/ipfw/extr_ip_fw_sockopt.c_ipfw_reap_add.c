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
struct ip_fw {struct ip_fw* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_UH_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 int /*<<< orphan*/  unref_rule_objects (struct ip_fw_chain*,struct ip_fw*) ; 

void
ipfw_reap_add(struct ip_fw_chain *chain, struct ip_fw **head,
    struct ip_fw *rule)
{

	IPFW_UH_WLOCK_ASSERT(chain);

	/* Unlink rule from everywhere */
	unref_rule_objects(chain, rule);

	rule->next = *head;
	*head = rule;
}