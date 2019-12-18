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
struct insn_emulation {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  set_hw_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  disable_insn_hw_mode ; 
 int /*<<< orphan*/  enable_insn_hw_mode ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int run_all_cpu_set_hw_mode(struct insn_emulation *insn, bool enable)
{
	if (!insn->ops->set_hw_mode)
		return -EINVAL;
	if (enable)
		on_each_cpu(enable_insn_hw_mode, (void *)insn, true);
	else
		on_each_cpu(disable_insn_hw_mode, (void *)insn, true);
	return 0;
}