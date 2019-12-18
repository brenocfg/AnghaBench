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
struct l_semid_ds {TYPE_1__ sem_perm; } ;
struct l_semid64_ds {TYPE_1__ sem_perm; } ;
typedef  int /*<<< orphan*/  linux_semid ;
typedef  scalar_t__ l_int ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ LINUX_IPC_64 ; 
 scalar_t__ SV_CURPROC_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_LP64 ; 
 int /*<<< orphan*/  bzero (struct l_semid_ds*,int) ; 
 int copyin (int /*<<< orphan*/ ,struct l_semid_ds*,int) ; 

__attribute__((used)) static int
linux_semid_pullup(l_int ver, struct l_semid64_ds *linux_semid64, caddr_t uaddr)
{
	struct l_semid_ds linux_semid;
	int error;

	if (ver == LINUX_IPC_64 || SV_CURPROC_FLAG(SV_LP64))
		return (copyin(uaddr, linux_semid64, sizeof(*linux_semid64)));
	else {
		error = copyin(uaddr, &linux_semid, sizeof(linux_semid));
		if (error != 0)
			return (error);

		bzero(linux_semid64, sizeof(*linux_semid64));

		linux_semid64->sem_perm.uid = linux_semid.sem_perm.uid;
		linux_semid64->sem_perm.gid = linux_semid.sem_perm.gid;
		linux_semid64->sem_perm.mode = linux_semid.sem_perm.mode;
		return (0);
	}
}