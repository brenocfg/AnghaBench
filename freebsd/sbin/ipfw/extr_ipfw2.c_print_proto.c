#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct show_state {scalar_t__ proto; int /*<<< orphan*/  flags; TYPE_1__* rule; } ;
struct format_opts {int dummy; } ;
struct buf_pr {int dummy; } ;
struct TYPE_6__ {int opcode; int len; } ;
typedef  TYPE_2__ ipfw_insn ;
struct TYPE_5__ {int act_ofs; TYPE_2__* cmd; } ;

/* Variables and functions */
 scalar_t__ F_LEN (TYPE_2__*) ; 
 int F_OR ; 
 int /*<<< orphan*/  HAVE_PROTO ; 
 scalar_t__ IPPROTO_IP ; 
 scalar_t__ IPPROTO_IPV6 ; 
#define  O_IP4 130 
#define  O_IP6 129 
#define  O_PROTO 128 
 int /*<<< orphan*/  bprintf (struct buf_pr*,char*) ; 
 TYPE_2__* print_opcode (struct buf_pr*,struct format_opts*,struct show_state*,int const) ; 

__attribute__((used)) static void
print_proto(struct buf_pr *bp, struct format_opts *fo,
    struct show_state *state)
{
	ipfw_insn *cmd;
	int l, proto, ip4, ip6;

	/* Count all O_PROTO, O_IP4, O_IP6 instructions. */
	proto = ip4 = ip6 = 0;
	for (l = state->rule->act_ofs, cmd = state->rule->cmd;
	    l > 0; l -= F_LEN(cmd), cmd += F_LEN(cmd)) {
		switch (cmd->opcode) {
		case O_PROTO:
			proto++;
			break;
		case O_IP4:
			ip4 = 1;
			if (cmd->len & F_OR)
				ip4++;
			break;
		case O_IP6:
			ip6 = 1;
			if (cmd->len & F_OR)
				ip6++;
			break;
		default:
			continue;
		}
	}
	if (proto == 0 && ip4 == 0 && ip6 == 0) {
		state->proto = IPPROTO_IP;
		state->flags |= HAVE_PROTO;
		bprintf(bp, " ip");
		return;
	}
	/* To handle the case { ip4 or ip6 }, print opcode with F_OR first */
	cmd = NULL;
	if (ip4 || ip6)
		cmd = print_opcode(bp, fo, state, ip4 > ip6 ? O_IP4: O_IP6);
	if (cmd != NULL && (cmd->len & F_OR))
		cmd = print_opcode(bp, fo, state, ip4 > ip6 ? O_IP6: O_IP4);
	if (cmd == NULL || (cmd->len & F_OR))
		for (l = proto; l > 0; l--) {
			cmd = print_opcode(bp, fo, state, O_PROTO);
			if (cmd == NULL || (cmd->len & F_OR) == 0)
				break;
		}
	/* Initialize proto, it is used by print_newports() */
	state->flags |= HAVE_PROTO;
	if (state->proto == 0 && ip6 != 0)
		state->proto = IPPROTO_IPV6;
}