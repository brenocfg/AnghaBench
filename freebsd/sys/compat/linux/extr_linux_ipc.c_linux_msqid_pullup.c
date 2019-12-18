#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct l_msqid_ds {scalar_t__ msg_qbytes; scalar_t__ msg_lqbytes; TYPE_1__ msg_perm; } ;
struct l_msqid64_ds {scalar_t__ msg_qbytes; scalar_t__ msg_lqbytes; TYPE_1__ msg_perm; } ;
typedef  int /*<<< orphan*/  linux_msqid ;
typedef  scalar_t__ l_int ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ LINUX_IPC_64 ; 
 scalar_t__ SV_CURPROC_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_LP64 ; 
 int /*<<< orphan*/  bzero (struct l_msqid_ds*,int) ; 
 int copyin (int /*<<< orphan*/ ,struct l_msqid_ds*,int) ; 

__attribute__((used)) static int
linux_msqid_pullup(l_int ver, struct l_msqid64_ds *linux_msqid64, caddr_t uaddr)
{
	struct l_msqid_ds linux_msqid;
	int error;

	if (ver == LINUX_IPC_64 || SV_CURPROC_FLAG(SV_LP64))
		return (copyin(uaddr, linux_msqid64, sizeof(*linux_msqid64)));
	else {
		error = copyin(uaddr, &linux_msqid, sizeof(linux_msqid));
		if (error != 0)
			return (error);

		bzero(linux_msqid64, sizeof(*linux_msqid64));

		linux_msqid64->msg_perm.uid = linux_msqid.msg_perm.uid;
		linux_msqid64->msg_perm.gid = linux_msqid.msg_perm.gid;
		linux_msqid64->msg_perm.mode = linux_msqid.msg_perm.mode;
		if (linux_msqid.msg_qbytes == 0)
			linux_msqid64->msg_qbytes = linux_msqid.msg_lqbytes;
		else
			linux_msqid64->msg_qbytes = linux_msqid.msg_qbytes;
		return (0);
	}
}