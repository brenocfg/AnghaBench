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
struct msqid_ds {int /*<<< orphan*/  msg_ctime; int /*<<< orphan*/  msg_rtime; int /*<<< orphan*/  msg_stime; int /*<<< orphan*/  msg_lrpid; int /*<<< orphan*/  msg_lspid; int /*<<< orphan*/  msg_qbytes; int /*<<< orphan*/  msg_qnum; int /*<<< orphan*/  msg_cbytes; int /*<<< orphan*/  msg_perm; } ;
struct l_msqid64_ds {int /*<<< orphan*/  msg_ctime; int /*<<< orphan*/  msg_rtime; int /*<<< orphan*/  msg_stime; int /*<<< orphan*/  msg_lrpid; int /*<<< orphan*/  msg_lspid; int /*<<< orphan*/  msg_qbytes; int /*<<< orphan*/  msg_qnum; int /*<<< orphan*/  msg_cbytes; int /*<<< orphan*/  msg_perm; } ;

/* Variables and functions */
 int /*<<< orphan*/  bsd_to_linux_ipc_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bsd_to_linux_msqid_ds(struct msqid_ds *bsp, struct l_msqid64_ds *lsp)
{

	bsd_to_linux_ipc_perm(&bsp->msg_perm, &lsp->msg_perm);
	lsp->msg_cbytes = bsp->msg_cbytes;
	lsp->msg_qnum = bsp->msg_qnum;
	lsp->msg_qbytes = bsp->msg_qbytes;
	lsp->msg_lspid = bsp->msg_lspid;
	lsp->msg_lrpid = bsp->msg_lrpid;
	lsp->msg_stime = bsp->msg_stime;
	lsp->msg_rtime = bsp->msg_rtime;
	lsp->msg_ctime = bsp->msg_ctime;
}