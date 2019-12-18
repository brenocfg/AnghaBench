#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ip_fw_chain {int n_rules; int /*<<< orphan*/ * map; } ;
struct TYPE_4__ {scalar_t__ opcode; } ;
struct TYPE_6__ {TYPE_2__* nat; TYPE_1__ o; } ;
typedef  TYPE_3__ ipfw_insn_nat ;
struct TYPE_5__ {int const id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_WLOCK_ASSERT (struct ip_fw_chain*) ; 
 scalar_t__ O_NAT ; 
 scalar_t__ ipfw_get_action (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flush_nat_ptrs(struct ip_fw_chain *chain, const int ix)
{
	ipfw_insn_nat *cmd;
	int i;

	IPFW_WLOCK_ASSERT(chain);
	for (i = 0; i < chain->n_rules; i++) {
		cmd = (ipfw_insn_nat *)ipfw_get_action(chain->map[i]);
		if (cmd->o.opcode == O_NAT && cmd->nat != NULL &&
			    (ix < 0 || cmd->nat->id == ix))
			cmd->nat = NULL;
	}
}