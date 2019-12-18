#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ip_fw_chain {TYPE_1__** map; int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int slot; int /*<<< orphan*/  rulenum; scalar_t__ rule_id; int /*<<< orphan*/  chain_id; } ;
struct ip_fw_args {int /*<<< orphan*/  flags; TYPE_2__ rule; } ;
struct TYPE_3__ {int /*<<< orphan*/  rulenum; scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_ARGS_REF ; 

__attribute__((used)) static inline void
set_match(struct ip_fw_args *args, int slot,
	struct ip_fw_chain *chain)
{
	args->rule.chain_id = chain->id;
	args->rule.slot = slot + 1; /* we use 0 as a marker */
	args->rule.rule_id = 1 + chain->map[slot]->id;
	args->rule.rulenum = chain->map[slot]->rulenum;
	args->flags |= IPFW_ARGS_REF;
}