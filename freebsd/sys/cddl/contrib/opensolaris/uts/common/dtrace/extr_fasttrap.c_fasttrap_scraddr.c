#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* vm_offset_t ;
struct thread {TYPE_2__* t_dtrace_sscr; struct proc* td_proc; } ;
struct proc {TYPE_1__* p_vmspace; } ;
struct TYPE_12__ {void* ftss_addr; void* ftsb_addr; } ;
typedef  TYPE_2__ fasttrap_scrspace_t ;
typedef  TYPE_2__ fasttrap_scrblock_t ;
struct TYPE_13__ {int /*<<< orphan*/  ftpc_mtx; int /*<<< orphan*/  ftpc_ascr; int /*<<< orphan*/  ftpc_fscr; int /*<<< orphan*/  ftpc_scrblks; } ;
typedef  TYPE_4__ fasttrap_proc_t ;
struct TYPE_11__ {int /*<<< orphan*/  vm_map; } ;

/* Variables and functions */
 int FASTTRAP_SCRBLOCK_SIZE ; 
 int FASTTRAP_SCRSPACE_SIZE ; 
 int KERN_SUCCESS ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SOLARIS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  VMFS_ANY_SPACE ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int /*<<< orphan*/  ftsb_next ; 
 int /*<<< orphan*/  ftss_next ; 
 TYPE_2__* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int vm_map_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

fasttrap_scrspace_t *
fasttrap_scraddr(struct thread *td, fasttrap_proc_t *fprc)
{
	fasttrap_scrblock_t *scrblk;
	fasttrap_scrspace_t *scrspc;
	struct proc *p;
	vm_offset_t addr;
	int error, i;

	scrspc = NULL;
	if (td->t_dtrace_sscr != NULL) {
		/* If the thread already has scratch space, we're done. */
		scrspc = (fasttrap_scrspace_t *)td->t_dtrace_sscr;
		return (scrspc);
	}

	p = td->td_proc;

	mutex_enter(&fprc->ftpc_mtx);
	if (LIST_EMPTY(&fprc->ftpc_fscr)) {
		/*
		 * No scratch space is available, so we'll map a new scratch
		 * space block into the traced process' address space.
		 */
		addr = 0;
		error = vm_map_find(&p->p_vmspace->vm_map, NULL, 0, &addr,
		    FASTTRAP_SCRBLOCK_SIZE, 0, VMFS_ANY_SPACE, VM_PROT_ALL,
		    VM_PROT_ALL, 0);
		if (error != KERN_SUCCESS)
			goto done;

		scrblk = malloc(sizeof(*scrblk), M_SOLARIS, M_WAITOK);
		scrblk->ftsb_addr = addr;
		LIST_INSERT_HEAD(&fprc->ftpc_scrblks, scrblk, ftsb_next);

		/*
		 * Carve the block up into chunks and put them on the free list.
		 */
		for (i = 0;
		    i < FASTTRAP_SCRBLOCK_SIZE / FASTTRAP_SCRSPACE_SIZE; i++) {
			scrspc = malloc(sizeof(*scrspc), M_SOLARIS, M_WAITOK);
			scrspc->ftss_addr = addr +
			    i * FASTTRAP_SCRSPACE_SIZE;
			LIST_INSERT_HEAD(&fprc->ftpc_fscr, scrspc,
			    ftss_next);
		}
	}

	/*
	 * Take the first scratch chunk off the free list, put it on the
	 * allocated list, and return its address.
	 */
	scrspc = LIST_FIRST(&fprc->ftpc_fscr);
	LIST_REMOVE(scrspc, ftss_next);
	LIST_INSERT_HEAD(&fprc->ftpc_ascr, scrspc, ftss_next);

	/*
	 * This scratch space is reserved for use by td until the thread exits.
	 */
	td->t_dtrace_sscr = scrspc;

done:
	mutex_exit(&fprc->ftpc_mtx);

	return (scrspc);
}