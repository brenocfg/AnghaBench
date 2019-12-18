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
struct TYPE_2__ {int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;
struct cpuid_regs_done {int /*<<< orphan*/  done; TYPE_1__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuid_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cpuid_smp_cpuid(void *cmd_block)
{
	struct cpuid_regs_done *cmd = cmd_block;

	cpuid_count(cmd->regs.eax, cmd->regs.ecx,
		    &cmd->regs.eax, &cmd->regs.ebx,
		    &cmd->regs.ecx, &cmd->regs.edx);

	complete(&cmd->done);
}