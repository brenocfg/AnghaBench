#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct show_state {TYPE_1__* rule; } ;
struct format_opts {int dummy; } ;
struct buf_pr {int dummy; } ;
struct TYPE_7__ {int opcode; } ;
typedef  TYPE_2__ ipfw_insn ;
struct TYPE_6__ {int act_ofs; TYPE_2__* cmd; } ;

/* Variables and functions */
 scalar_t__ F_LEN (TYPE_2__*) ; 
 int O_NOP ; 
 int /*<<< orphan*/  print_instruction (struct buf_pr*,struct format_opts*,struct show_state*,TYPE_2__*) ; 

__attribute__((used)) static ipfw_insn *
print_opcode(struct buf_pr *bp, struct format_opts *fo,
    struct show_state *state, int opcode)
{
	ipfw_insn *cmd;
	int l;

	for (l = state->rule->act_ofs, cmd = state->rule->cmd;
	    l > 0; l -= F_LEN(cmd), cmd += F_LEN(cmd)) {
		/* We use zero opcode to print the rest of options */
		if (opcode >= 0 && cmd->opcode != opcode)
			continue;
		/*
		 * Skip O_NOP, when we printing the rest
		 * of options, it will be handled separately.
		 */
		if (cmd->opcode == O_NOP && opcode != O_NOP)
			continue;
		if (!print_instruction(bp, fo, state, cmd))
			continue;
		return (cmd);
	}
	return (NULL);
}