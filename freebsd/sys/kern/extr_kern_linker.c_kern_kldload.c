#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_ucred; } ;
typedef  TYPE_1__* linker_file_t ;
struct TYPE_3__ {int id; int /*<<< orphan*/  userrefs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRIV_KLD_LOAD ; 
 int /*<<< orphan*/  TD_TO_VNET (struct thread*) ; 
 int /*<<< orphan*/  kld_sx ; 
 int linker_load_module (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int securelevel_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
kern_kldload(struct thread *td, const char *file, int *fileid)
{
	const char *kldname, *modname;
	linker_file_t lf;
	int error;

	if ((error = securelevel_gt(td->td_ucred, 0)) != 0)
		return (error);

	if ((error = priv_check(td, PRIV_KLD_LOAD)) != 0)
		return (error);

	/*
	 * It is possible that kldloaded module will attach a new ifnet,
	 * so vnet context must be set when this ocurs.
	 */
	CURVNET_SET(TD_TO_VNET(td));

	/*
	 * If file does not contain a qualified name or any dot in it
	 * (kldname.ko, or kldname.ver.ko) treat it as an interface
	 * name.
	 */
	if (strchr(file, '/') || strchr(file, '.')) {
		kldname = file;
		modname = NULL;
	} else {
		kldname = NULL;
		modname = file;
	}

	sx_xlock(&kld_sx);
	error = linker_load_module(kldname, modname, NULL, NULL, &lf);
	if (error) {
		sx_xunlock(&kld_sx);
		goto done;
	}
	lf->userrefs++;
	if (fileid != NULL)
		*fileid = lf->id;
	sx_xunlock(&kld_sx);

done:
	CURVNET_RESTORE();
	return (error);
}