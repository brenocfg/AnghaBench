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
struct ifvxlancmd {int /*<<< orphan*/  vxlcmd_flags; } ;
struct afswtch {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  VXLAN_CMD_FLAG_FLUSH_ALL ; 
 int /*<<< orphan*/  VXLAN_CMD_FLUSH ; 
 int /*<<< orphan*/  bzero (struct ifvxlancmd*,int) ; 
 scalar_t__ do_cmd (int,int /*<<< orphan*/ ,struct ifvxlancmd*,int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 

__attribute__((used)) static void
setvxlan_flush(const char *val, int d, int s, const struct afswtch *afp)
{
	struct ifvxlancmd cmd;

	bzero(&cmd, sizeof(cmd));
	if (d != 0)
		cmd.vxlcmd_flags |= VXLAN_CMD_FLAG_FLUSH_ALL;

	if (do_cmd(s, VXLAN_CMD_FLUSH, &cmd, sizeof(cmd), 1) < 0)
		err(1, "VXLAN_CMD_FLUSH");
}