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
struct sbuf {int dummy; } ;
struct nvme_command {int /*<<< orphan*/  cdw15; int /*<<< orphan*/  cdw14; int /*<<< orphan*/  cdw13; int /*<<< orphan*/  cdw12; int /*<<< orphan*/  cdw11; int /*<<< orphan*/  cdw10; scalar_t__ prp2; scalar_t__ prp1; int /*<<< orphan*/  nsid; int /*<<< orphan*/  fuse; int /*<<< orphan*/  opc; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
nvme_cmd_sbuf(const struct nvme_command *cmd, struct sbuf *sb)
{

	/*
	 * cid, rsvd areas and mptr not printed, since they are used
	 * only internally by the SIM.
	 */
	sbuf_printf(sb,
	    "opc=%x fuse=%x nsid=%x prp1=%llx prp2=%llx cdw=%x %x %x %x %x %x",
	    cmd->opc, cmd->fuse, cmd->nsid,
	    (unsigned long long)cmd->prp1, (unsigned long long)cmd->prp2,
	    cmd->cdw10, cmd->cdw11, cmd->cdw12,
	    cmd->cdw13, cmd->cdw14, cmd->cdw15);
}