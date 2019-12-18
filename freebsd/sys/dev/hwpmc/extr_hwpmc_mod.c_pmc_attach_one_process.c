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
struct proc {int p_flag; int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_textvp; int /*<<< orphan*/  p_comm; } ;
struct pmc_process {TYPE_1__* pp_pmcs; } ;
struct pmc {int pm_flags; TYPE_2__* pm_owner; } ;
struct TYPE_4__ {int po_flags; } ;
struct TYPE_3__ {struct pmc* pp_pmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATT ; 
 int EBUSY ; 
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  PMCDBG5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct pmc*,int,struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMC_FLAG_ALLOCATE ; 
 int PMC_F_ATTACHED_TO_OWNER ; 
 int PMC_F_ATTACH_DONE ; 
 int PMC_F_NEEDS_LOGFILE ; 
 scalar_t__ PMC_IS_SAMPLING_MODE (int /*<<< orphan*/ ) ; 
 int PMC_PO_OWNS_LOGFILE ; 
 int /*<<< orphan*/  PMC_TO_MODE (struct pmc*) ; 
 int PMC_TO_ROWINDEX (struct pmc*) ; 
 int /*<<< orphan*/  PRC ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_HWPMC ; 
 int P_KPROC ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* kernelname ; 
 struct pmc_process* pmc_find_process_descriptor (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmc_getfilename (int /*<<< orphan*/ ,char**,char**) ; 
 int /*<<< orphan*/  pmc_link_target_process (struct pmc*,struct pmc_process*) ; 
 int /*<<< orphan*/  pmc_log_process_mappings (TYPE_2__*,struct proc*) ; 
 int /*<<< orphan*/  pmc_sx ; 
 int /*<<< orphan*/  pmclog_process_pmcattach (struct pmc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pmc_attach_one_process(struct proc *p, struct pmc *pm)
{
	int ri, error;
	char *fullpath, *freepath;
	struct pmc_process	*pp;

	sx_assert(&pmc_sx, SX_XLOCKED);

	PMCDBG5(PRC,ATT,2, "attach-one pm=%p ri=%d proc=%p (%d, %s)", pm,
	    PMC_TO_ROWINDEX(pm), p, p->p_pid, p->p_comm);

	/*
	 * Locate the process descriptor corresponding to process 'p',
	 * allocating space as needed.
	 *
	 * Verify that rowindex 'pm_rowindex' is free in the process
	 * descriptor.
	 *
	 * If not, allocate space for a descriptor and link the
	 * process descriptor and PMC.
	 */
	ri = PMC_TO_ROWINDEX(pm);

	/* mark process as using HWPMCs */
	PROC_LOCK(p);
	p->p_flag |= P_HWPMC;
	PROC_UNLOCK(p);

	if ((pp = pmc_find_process_descriptor(p, PMC_FLAG_ALLOCATE)) == NULL) {
		error = ENOMEM;
		goto fail;
	}

	if (pp->pp_pmcs[ri].pp_pmc == pm) {/* already present at slot [ri] */
		error = EEXIST;
		goto fail;
	}

	if (pp->pp_pmcs[ri].pp_pmc != NULL) {
		error = EBUSY;
		goto fail;
	}

	pmc_link_target_process(pm, pp);

	if (PMC_IS_SAMPLING_MODE(PMC_TO_MODE(pm)) &&
	    (pm->pm_flags & PMC_F_ATTACHED_TO_OWNER) == 0)
		pm->pm_flags |= PMC_F_NEEDS_LOGFILE;

	pm->pm_flags |= PMC_F_ATTACH_DONE; /* mark as attached */

	/* issue an attach event to a configured log file */
	if (pm->pm_owner->po_flags & PMC_PO_OWNS_LOGFILE) {
		if (p->p_flag & P_KPROC) {
			fullpath = kernelname;
			freepath = NULL;
		} else {
			pmc_getfilename(p->p_textvp, &fullpath, &freepath);
			pmclog_process_pmcattach(pm, p->p_pid, fullpath);
		}
		free(freepath, M_TEMP);
		if (PMC_IS_SAMPLING_MODE(PMC_TO_MODE(pm)))
			pmc_log_process_mappings(pm->pm_owner, p);
	}

	return (0);
 fail:
	PROC_LOCK(p);
	p->p_flag &= ~P_HWPMC;
	PROC_UNLOCK(p);
	return (error);
}