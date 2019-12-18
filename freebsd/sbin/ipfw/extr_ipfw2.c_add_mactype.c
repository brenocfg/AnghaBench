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
typedef  int /*<<< orphan*/  ipfw_insn_u16 ;
struct TYPE_4__ {int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ ipfw_insn ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
 int /*<<< orphan*/  IPPROTO_ETHERTYPE ; 
 int /*<<< orphan*/  O_MAC_TYPE ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fill_newports (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static ipfw_insn *
add_mactype(ipfw_insn *cmd, char *av, int cblen)
{
	if (!av)
		errx(EX_DATAERR, "missing MAC type");
	if (strcmp(av, "any") != 0) { /* we have a non-null type */
		fill_newports((ipfw_insn_u16 *)cmd, av, IPPROTO_ETHERTYPE,
		    cblen);
		cmd->opcode = O_MAC_TYPE;
		return cmd;
	} else
		return NULL;
}