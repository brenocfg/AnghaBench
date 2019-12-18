#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct show_state {TYPE_6__* rule; } ;
struct format_opts {int dummy; } ;
struct buf_pr {int dummy; } ;
struct TYPE_7__ {scalar_t__ opcode; } ;
typedef  TYPE_1__ ipfw_insn ;
struct TYPE_8__ {int cmd_len; int act_ofs; } ;

/* Variables and functions */
 TYPE_1__* ACTION_PTR (TYPE_6__*) ; 
 scalar_t__ F_LEN (TYPE_1__*) ; 
 int /*<<< orphan*/  print_action_instruction (struct buf_pr*,struct format_opts*,struct show_state*,TYPE_1__*) ; 

__attribute__((used)) static ipfw_insn *
print_action(struct buf_pr *bp, struct format_opts *fo,
    struct show_state *state, uint8_t opcode)
{
	ipfw_insn *cmd;
	int l;

	for (l = state->rule->cmd_len - state->rule->act_ofs,
	    cmd = ACTION_PTR(state->rule); l > 0;
	    l -= F_LEN(cmd), cmd += F_LEN(cmd)) {
		if (cmd->opcode != opcode)
			continue;
		if (!print_action_instruction(bp, fo, state, cmd))
			continue;
		return (cmd);
	}
	return (NULL);
}