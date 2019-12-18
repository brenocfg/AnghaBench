#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct insn_emulation {int current_mode; TYPE_1__* ops; } ;
typedef  enum insn_emulation_mode { ____Placeholder_insn_emulation_mode } insn_emulation_mode ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  INSN_EMULATE 130 
#define  INSN_HW 129 
#define  INSN_UNDEF 128 
 int /*<<< orphan*/  pr_notice (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_emulation_hooks (TYPE_1__*) ; 
 int /*<<< orphan*/  remove_emulation_hooks (TYPE_1__*) ; 
 int run_all_cpu_set_hw_mode (struct insn_emulation*,int) ; 

__attribute__((used)) static int update_insn_emulation_mode(struct insn_emulation *insn,
				       enum insn_emulation_mode prev)
{
	int ret = 0;

	switch (prev) {
	case INSN_UNDEF: /* Nothing to be done */
		break;
	case INSN_EMULATE:
		remove_emulation_hooks(insn->ops);
		break;
	case INSN_HW:
		if (!run_all_cpu_set_hw_mode(insn, false))
			pr_notice("Disabled %s support\n", insn->ops->name);
		break;
	}

	switch (insn->current_mode) {
	case INSN_UNDEF:
		break;
	case INSN_EMULATE:
		register_emulation_hooks(insn->ops);
		break;
	case INSN_HW:
		ret = run_all_cpu_set_hw_mode(insn, true);
		if (!ret)
			pr_notice("Enabled %s support\n", insn->ops->name);
		break;
	}

	return ret;
}