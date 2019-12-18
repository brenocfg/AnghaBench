#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_ucred; } ;
typedef  TYPE_1__* linker_file_t ;
struct TYPE_4__ {scalar_t__ userrefs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int ENOENT ; 
 int /*<<< orphan*/  FILE ; 
 int /*<<< orphan*/  KLD_DPF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PRIV_KLD_UNLOAD ; 
 int /*<<< orphan*/  TD_TO_VNET (struct thread*) ; 
 int /*<<< orphan*/  kld_sx ; 
 int linker_file_unload (TYPE_1__*,int) ; 
 TYPE_1__* linker_find_file_by_id (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int securelevel_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
kern_kldunload(struct thread *td, int fileid, int flags)
{
	linker_file_t lf;
	int error = 0;

	if ((error = securelevel_gt(td->td_ucred, 0)) != 0)
		return (error);

	if ((error = priv_check(td, PRIV_KLD_UNLOAD)) != 0)
		return (error);

	CURVNET_SET(TD_TO_VNET(td));
	sx_xlock(&kld_sx);
	lf = linker_find_file_by_id(fileid);
	if (lf) {
		KLD_DPF(FILE, ("kldunload: lf->userrefs=%d\n", lf->userrefs));

		if (lf->userrefs == 0) {
			/*
			 * XXX: maybe LINKER_UNLOAD_FORCE should override ?
			 */
			printf("kldunload: attempt to unload file that was"
			    " loaded by the kernel\n");
			error = EBUSY;
		} else {
			lf->userrefs--;
			error = linker_file_unload(lf, flags);
			if (error)
				lf->userrefs++;
		}
	} else
		error = ENOENT;
	sx_xunlock(&kld_sx);

	CURVNET_RESTORE();
	return (error);
}