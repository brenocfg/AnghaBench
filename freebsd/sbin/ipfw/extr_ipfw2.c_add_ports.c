#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ipfw_insn_u16 ;
struct TYPE_4__ {int opcode; } ;
typedef  TYPE_1__ ipfw_insn ;

/* Variables and functions */
 int /*<<< orphan*/  f_reserved_keywords ; 
 scalar_t__ fill_newports (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int match_token (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ipfw_insn *
add_ports(ipfw_insn *cmd, char *av, u_char proto, int opcode, int cblen)
{

	if (match_token(f_reserved_keywords, av) != -1)
		return (NULL);

	if (fill_newports((ipfw_insn_u16 *)cmd, av, proto, cblen)) {
		/* XXX todo: check that we have a protocol with ports */
		cmd->opcode = opcode;
		return cmd;
	}
	return NULL;
}