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
struct ip_fw {int cmd_len; TYPE_1__* cmd; } ;
struct TYPE_3__ {int opcode; } ;
typedef  TYPE_1__ ipfw_insn ;

/* Variables and functions */
 int F_LEN (TYPE_1__*) ; 
#define  O_CHECK_STATE 131 
#define  O_KEEP_STATE 130 
#define  O_LIMIT 129 
#define  O_PROBE_STATE 128 

int
ipfw_is_dyn_rule(struct ip_fw *rule)
{
	int cmdlen, l;
	ipfw_insn *cmd;

	l = rule->cmd_len;
	cmd = rule->cmd;
	cmdlen = 0;
	for ( ;	l > 0 ; l -= cmdlen, cmd += cmdlen) {
		cmdlen = F_LEN(cmd);

		switch (cmd->opcode) {
		case O_LIMIT:
		case O_KEEP_STATE:
		case O_PROBE_STATE:
		case O_CHECK_STATE:
			return (1);
		}
	}

	return (0);
}