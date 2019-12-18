#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; } ;
struct TYPE_5__ {scalar_t__ msg_qbytes; TYPE_1__ msg_perm; } ;
struct msqid_kernel {TYPE_2__ u; } ;
struct TYPE_6__ {int msgmni; int msgtql; } ;

/* Variables and functions */
 int EBUSY ; 
 int MSG_LOCKED ; 
 int /*<<< orphan*/  M_MSG ; 
 int /*<<< orphan*/  free (struct msqid_kernel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_sysvmsg_destroy (struct msqid_kernel*) ; 
 int /*<<< orphan*/  mac_sysvmsq_destroy (struct msqid_kernel*) ; 
 int /*<<< orphan*/  msg32_syscalls ; 
 scalar_t__ msg_prison_slot ; 
 int /*<<< orphan*/  msg_syscalls ; 
 struct msqid_kernel* msghdrs ; 
 TYPE_3__ msginfo ; 
 struct msqid_kernel* msgmaps ; 
 struct msqid_kernel* msgpool ; 
 int /*<<< orphan*/  msq_mtx ; 
 struct msqid_kernel* msqids ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osd_jail_deregister (scalar_t__) ; 
 int /*<<< orphan*/  syscall32_helper_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscall_helper_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
msgunload()
{
	struct msqid_kernel *msqkptr;
	int msqid;
#ifdef MAC
	int i;
#endif

	syscall_helper_unregister(msg_syscalls);
#ifdef COMPAT_FREEBSD32
	syscall32_helper_unregister(msg32_syscalls);
#endif

	for (msqid = 0; msqid < msginfo.msgmni; msqid++) {
		msqkptr = &msqids[msqid];
		if (msqkptr->u.msg_qbytes != 0 ||
		    (msqkptr->u.msg_perm.mode & MSG_LOCKED) != 0)
			break;
	}
	if (msqid != msginfo.msgmni)
		return (EBUSY);

	if (msg_prison_slot != 0)
		osd_jail_deregister(msg_prison_slot);
#ifdef MAC
	for (i = 0; i < msginfo.msgtql; i++)
		mac_sysvmsg_destroy(&msghdrs[i]);
	for (msqid = 0; msqid < msginfo.msgmni; msqid++)
		mac_sysvmsq_destroy(&msqids[msqid]);
#endif
	free(msgpool, M_MSG);
	free(msgmaps, M_MSG);
	free(msghdrs, M_MSG);
	free(msqids, M_MSG);
	mtx_destroy(&msq_mtx);
	return (0);
}