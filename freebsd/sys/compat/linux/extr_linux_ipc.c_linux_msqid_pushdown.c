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
struct l_msqid_ds {scalar_t__ msg_stime; scalar_t__ msg_rtime; scalar_t__ msg_ctime; scalar_t__ msg_cbytes; scalar_t__ msg_lcbytes; scalar_t__ msg_qnum; scalar_t__ msg_qbytes; scalar_t__ msg_lqbytes; int /*<<< orphan*/  msg_lrpid; int /*<<< orphan*/  msg_lspid; int /*<<< orphan*/  msg_perm; } ;
struct l_msqid64_ds {scalar_t__ msg_stime; scalar_t__ msg_rtime; scalar_t__ msg_ctime; scalar_t__ msg_cbytes; scalar_t__ msg_lcbytes; scalar_t__ msg_qnum; scalar_t__ msg_qbytes; scalar_t__ msg_lqbytes; int /*<<< orphan*/  msg_lrpid; int /*<<< orphan*/  msg_lspid; int /*<<< orphan*/  msg_perm; } ;
typedef  int /*<<< orphan*/  linux_msqid ;
typedef  scalar_t__ l_int ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EOVERFLOW ; 
 scalar_t__ LINUX_IPC_64 ; 
 scalar_t__ SV_CURPROC_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_LP64 ; 
 scalar_t__ USHRT_MAX ; 
 int /*<<< orphan*/  bzero (struct l_msqid_ds*,int) ; 
 int copyout (struct l_msqid_ds*,int /*<<< orphan*/ ,int) ; 
 int linux_ipc64_perm_to_ipc_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
linux_msqid_pushdown(l_int ver, struct l_msqid64_ds *linux_msqid64, caddr_t uaddr)
{
	struct l_msqid_ds linux_msqid;
	int error;

	if (ver == LINUX_IPC_64 || SV_CURPROC_FLAG(SV_LP64))
		return (copyout(linux_msqid64, uaddr, sizeof(*linux_msqid64)));
	else {
		bzero(&linux_msqid, sizeof(linux_msqid));

		error = linux_ipc64_perm_to_ipc_perm(&linux_msqid64->msg_perm,
		    &linux_msqid.msg_perm);
		if (error != 0)
			return (error);

		linux_msqid.msg_stime = linux_msqid64->msg_stime;
		linux_msqid.msg_rtime = linux_msqid64->msg_rtime;
		linux_msqid.msg_ctime = linux_msqid64->msg_ctime;

		if (linux_msqid64->msg_cbytes > USHRT_MAX)
			linux_msqid.msg_cbytes = USHRT_MAX;
		else
			linux_msqid.msg_cbytes = linux_msqid64->msg_cbytes;
		linux_msqid.msg_lcbytes = linux_msqid64->msg_cbytes;
		if (linux_msqid64->msg_qnum > USHRT_MAX)
			linux_msqid.msg_qnum = USHRT_MAX;
		else
			linux_msqid.msg_qnum = linux_msqid64->msg_qnum;
		if (linux_msqid64->msg_qbytes > USHRT_MAX)
			linux_msqid.msg_qbytes = USHRT_MAX;
		else
			linux_msqid.msg_qbytes = linux_msqid64->msg_qbytes;
		linux_msqid.msg_lqbytes = linux_msqid64->msg_qbytes;
		linux_msqid.msg_lspid = linux_msqid64->msg_lspid;
		linux_msqid.msg_lrpid = linux_msqid64->msg_lrpid;

		/* Linux does not check overflow */
		if (linux_msqid.msg_stime != linux_msqid64->msg_stime ||
		    linux_msqid.msg_rtime != linux_msqid64->msg_rtime ||
		    linux_msqid.msg_ctime != linux_msqid64->msg_ctime)
			return (EOVERFLOW);

		return (copyout(&linux_msqid, uaddr, sizeof(linux_msqid)));
	}
}