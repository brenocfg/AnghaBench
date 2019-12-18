#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct TYPE_3__ {int /*<<< orphan*/  pipc_mode; int /*<<< orphan*/  pipc_gid; int /*<<< orphan*/  pipc_uid; } ;
struct TYPE_4__ {TYPE_1__ ar_arg_pipc_perm; } ;
struct kaudit_record {TYPE_2__ k_ar; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_POSIX_IPC_PERM ; 
 int /*<<< orphan*/  ARG_SET_VALID (struct kaudit_record*,int /*<<< orphan*/ ) ; 
 struct kaudit_record* currecord () ; 

void
audit_arg_posix_ipc_perm(uid_t uid, gid_t gid, mode_t mode)
{
	struct kaudit_record *ar;

	ar = currecord();
	if (ar == NULL)
		return;

	ar->k_ar.ar_arg_pipc_perm.pipc_uid = uid;
	ar->k_ar.ar_arg_pipc_perm.pipc_gid = gid;
	ar->k_ar.ar_arg_pipc_perm.pipc_mode = mode;
	ARG_SET_VALID(ar, ARG_POSIX_IPC_PERM);
}