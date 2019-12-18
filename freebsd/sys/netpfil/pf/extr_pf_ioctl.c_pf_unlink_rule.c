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
struct pf_rulequeue {int dummy; } ;
struct pf_rule {int /*<<< orphan*/  rule_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFRULE_REFS ; 
 int /*<<< orphan*/  PF_RULES_WASSERT () ; 
 int /*<<< orphan*/  PF_UNLNKDRULES_LOCK () ; 
 int /*<<< orphan*/  PF_UNLNKDRULES_UNLOCK () ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct pf_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct pf_rulequeue*,struct pf_rule*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pf_unlinked_rules ; 
 int /*<<< orphan*/  entries ; 

__attribute__((used)) static void
pf_unlink_rule(struct pf_rulequeue *rulequeue, struct pf_rule *rule)
{

	PF_RULES_WASSERT();

	TAILQ_REMOVE(rulequeue, rule, entries);

	PF_UNLNKDRULES_LOCK();
	rule->rule_flag |= PFRULE_REFS;
	TAILQ_INSERT_TAIL(&V_pf_unlinked_rules, rule, entries);
	PF_UNLNKDRULES_UNLOCK();
}