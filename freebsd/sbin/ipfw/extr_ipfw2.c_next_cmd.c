#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ipfw_insn ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_LENGTH (int,int /*<<< orphan*/ ) ; 
 scalar_t__ F_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ipfw_insn *
next_cmd(ipfw_insn *cmd, int *len)
{
	*len -= F_LEN(cmd);
	CHECK_LENGTH(*len, 0);
	cmd += F_LEN(cmd);
	bzero(cmd, sizeof(*cmd));
	return cmd;
}