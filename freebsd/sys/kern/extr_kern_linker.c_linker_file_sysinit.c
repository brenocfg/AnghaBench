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
struct sysinit {scalar_t__ subsystem; scalar_t__ order; int /*<<< orphan*/  udata; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* linker_file_t ;
struct TYPE_4__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILE ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  KLD_DPF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 scalar_t__ SI_SUB_DUMMY ; 
 int /*<<< orphan*/  kld_sx ; 
 scalar_t__ linker_file_lookup_set (TYPE_1__*,char*,struct sysinit***,struct sysinit***,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
linker_file_sysinit(linker_file_t lf)
{
	struct sysinit **start, **stop, **sipp, **xipp, *save;

	KLD_DPF(FILE, ("linker_file_sysinit: calling SYSINITs for %s\n",
	    lf->filename));

	sx_assert(&kld_sx, SA_XLOCKED);

	if (linker_file_lookup_set(lf, "sysinit_set", &start, &stop, NULL) != 0)
		return;
	/*
	 * Perform a bubble sort of the system initialization objects by
	 * their subsystem (primary key) and order (secondary key).
	 *
	 * Since some things care about execution order, this is the operation
	 * which ensures continued function.
	 */
	for (sipp = start; sipp < stop; sipp++) {
		for (xipp = sipp + 1; xipp < stop; xipp++) {
			if ((*sipp)->subsystem < (*xipp)->subsystem ||
			    ((*sipp)->subsystem == (*xipp)->subsystem &&
			    (*sipp)->order <= (*xipp)->order))
				continue;	/* skip */
			save = *sipp;
			*sipp = *xipp;
			*xipp = save;
		}
	}

	/*
	 * Traverse the (now) ordered list of system initialization tasks.
	 * Perform each task, and continue on to the next task.
	 */
	sx_xunlock(&kld_sx);
	mtx_lock(&Giant);
	for (sipp = start; sipp < stop; sipp++) {
		if ((*sipp)->subsystem == SI_SUB_DUMMY)
			continue;	/* skip dummy task(s) */

		/* Call function */
		(*((*sipp)->func)) ((*sipp)->udata);
	}
	mtx_unlock(&Giant);
	sx_xlock(&kld_sx);
}