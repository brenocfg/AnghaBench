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
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EBUSY ; 
 int EOPNOTSUPP ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  SY_THR_STATIC_KLD ; 
 int /*<<< orphan*/ * nfsd_call_nfscl ; 
 int /*<<< orphan*/ * nfsd_call_nfscommon ; 
 int /*<<< orphan*/ * nfsd_call_nfsd ; 
 int /*<<< orphan*/ * nfsd_call_nfsserver ; 
 int /*<<< orphan*/  nfssvc_syscalls ; 
 int syscall_helper_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscall_helper_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfssvc_modevent(module_t mod, int type, void *data)
{
	int error = 0;

	switch (type) {
	case MOD_LOAD:
		error = syscall_helper_register(nfssvc_syscalls,
		    SY_THR_STATIC_KLD);
		break;

	case MOD_UNLOAD:
		if (nfsd_call_nfsserver != NULL || nfsd_call_nfscommon != NULL
		    || nfsd_call_nfscl != NULL || nfsd_call_nfsd != NULL) {
			error = EBUSY;
			break;
		}
		syscall_helper_unregister(nfssvc_syscalls);
		break;
	default:
		error = EOPNOTSUPP;
		break;
	}
	return error;
}