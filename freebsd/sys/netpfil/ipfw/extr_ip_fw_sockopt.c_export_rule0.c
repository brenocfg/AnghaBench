#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ip_fw_rule0 {int cmd_len; int _pad; TYPE_4__* cmd; int /*<<< orphan*/  pcnt; int /*<<< orphan*/  set; int /*<<< orphan*/  rulenum; int /*<<< orphan*/  act_ofs; } ;
struct ip_fw_bcounter0 {int dummy; } ;
struct ip_fw {int cmd_len; int flags; int /*<<< orphan*/  cmd; int /*<<< orphan*/  set; int /*<<< orphan*/  rulenum; int /*<<< orphan*/  act_ofs; } ;
struct TYPE_8__ {int conn_limit; } ;
typedef  TYPE_2__ ipfw_insn_limit ;
struct TYPE_7__ {int /*<<< orphan*/  kidx; int /*<<< orphan*/  glob; } ;
struct TYPE_9__ {char* name; TYPE_1__ p; } ;
typedef  TYPE_3__ ipfw_insn_if ;
struct TYPE_10__ {int opcode; int arg1; } ;
typedef  TYPE_4__ ipfw_insn ;

/* Variables and functions */
 int F_LEN (TYPE_4__*) ; 
 int IPFW_RULE_NOOPT ; 
 int IP_FW_NAT44_GLOBAL ; 
 void* IP_FW_TABLEARG ; 
 int IP_FW_TARG ; 
#define  O_CALLRETURN 144 
#define  O_DIVERT 143 
#define  O_LIMIT 142 
#define  O_NAT 141 
#define  O_NETGRAPH 140 
#define  O_NGTEE 139 
#define  O_PIPE 138 
#define  O_QUEUE 137 
#define  O_RECV 136 
#define  O_SETDSCP 135 
#define  O_SETFIB 134 
#define  O_SKIPTO 133 
#define  O_TAG 132 
#define  O_TAGGED 131 
#define  O_TEE 130 
#define  O_VIA 129 
#define  O_XMIT 128 
 int /*<<< orphan*/  export_cntr0_base (struct ip_fw*,struct ip_fw_bcounter0*) ; 
 int /*<<< orphan*/  memcpy (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ip_fw_rule0*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
export_rule0(struct ip_fw *krule, struct ip_fw_rule0 *urule, int len)
{
	int cmdlen, l;
	ipfw_insn *cmd;
	ipfw_insn_limit *lcmd;
	ipfw_insn_if *cmdif;

	/* copy header */
	memset(urule, 0, len);
	urule->act_ofs = krule->act_ofs;
	urule->cmd_len = krule->cmd_len;
	urule->rulenum = krule->rulenum;
	urule->set = krule->set;
	if ((krule->flags & IPFW_RULE_NOOPT) != 0)
		urule->_pad |= 1;

	/* Copy opcodes */
	memcpy(urule->cmd, krule->cmd, krule->cmd_len * sizeof(uint32_t));

	/* Export counters */
	export_cntr0_base(krule, (struct ip_fw_bcounter0 *)&urule->pcnt);

	/*
	 * Alter opcodes:
	 * 1) convert tablearg value from 0 to 65535
	 * 2) Remove highest bit from O_SETFIB/O_SETDSCP values.
	 * 3) convert table number in iface opcodes to int
	 */
	l = urule->cmd_len;
	cmd = urule->cmd;
	cmdlen = 0;

	for ( ;	l > 0 ; l -= cmdlen, cmd += cmdlen) {
		cmdlen = F_LEN(cmd);

		switch (cmd->opcode) {
		/* Opcodes supporting tablearg */
		case O_TAG:
		case O_TAGGED:
		case O_PIPE:
		case O_QUEUE:
		case O_DIVERT:
		case O_TEE:
		case O_SKIPTO:
		case O_CALLRETURN:
		case O_NETGRAPH:
		case O_NGTEE:
		case O_NAT:
			if (cmd->arg1 == IP_FW_TARG)
				cmd->arg1 = IP_FW_TABLEARG;
			else if (cmd->arg1 == IP_FW_NAT44_GLOBAL)
				cmd->arg1 = 0;
			break;
		case O_SETFIB:
		case O_SETDSCP:
			if (cmd->arg1 == IP_FW_TARG)
				cmd->arg1 = IP_FW_TABLEARG;
			else
				cmd->arg1 &= ~0x8000;
			break;
		case O_LIMIT:
			lcmd = (ipfw_insn_limit *)cmd;
			if (lcmd->conn_limit == IP_FW_TARG)
				lcmd->conn_limit = IP_FW_TABLEARG;
			break;
		/* Interface tables */
		case O_XMIT:
		case O_RECV:
		case O_VIA:
			/* Interface table, possibly */
			cmdif = (ipfw_insn_if *)cmd;
			if (cmdif->name[0] != '\1')
				break;

			cmdif->p.glob = cmdif->p.kidx;
			break;
		}
	}
}