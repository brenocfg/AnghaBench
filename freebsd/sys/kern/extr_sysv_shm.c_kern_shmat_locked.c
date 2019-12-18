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
typedef  void* vm_size_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int vm_offset_t ;
struct thread {int* td_retval; int /*<<< orphan*/  td_ucred; struct proc* td_proc; } ;
struct shmmap_state {int shmid; int va; } ;
struct TYPE_5__ {int shm_segsz; int /*<<< orphan*/  shm_nattch; int /*<<< orphan*/  shm_atime; int /*<<< orphan*/  shm_lpid; int /*<<< orphan*/  shm_perm; } ;
struct shmid_kernel {TYPE_2__ u; int /*<<< orphan*/  object; } ;
struct proc {int /*<<< orphan*/  p_pid; TYPE_1__* p_vmspace; } ;
struct prison {int dummy; } ;
struct TYPE_6__ {int shmseg; } ;
struct TYPE_4__ {int /*<<< orphan*/  vm_map; scalar_t__ vm_daddr; struct shmmap_state* vm_shm; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_SVIPC_ID (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_VALUE (int) ; 
 int EINVAL ; 
 int EMFILE ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int IPC_R ; 
 int IPC_W ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int KERN_SUCCESS ; 
 int MAP_INHERIT_SHARE ; 
 int MAP_PREFAULT_PARTIAL ; 
 int MAP_REMAP ; 
 int /*<<< orphan*/  M_SHM ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  RLIMIT_DATA ; 
 int SHMLBA ; 
 int SHM_RDONLY ; 
 int SHM_REMAP ; 
 int SHM_RND ; 
 int /*<<< orphan*/  SYSVSHM_ASSERT_LOCKED () ; 
 int VMFS_NO_SPACE ; 
 int VMFS_OPTIMAL_SPACE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 
 int ipcperm (struct thread*,int /*<<< orphan*/ *,int) ; 
 int lim_max (struct thread*,int /*<<< orphan*/ ) ; 
 int mac_sysvshm_check_shmat (int /*<<< orphan*/ ,struct shmid_kernel*,int) ; 
 struct shmmap_state* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* round_page (int) ; 
 int rounddown2 (int,int) ; 
 struct prison* shm_find_prison (int /*<<< orphan*/ ) ; 
 struct shmid_kernel* shm_find_segment (struct prison*,int,int) ; 
 TYPE_3__ shminfo ; 
 int /*<<< orphan*/  time_second ; 
 int vm_map_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_reference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kern_shmat_locked(struct thread *td, int shmid, const void *shmaddr,
    int shmflg)
{
	struct prison *rpr;
	struct proc *p = td->td_proc;
	struct shmid_kernel *shmseg;
	struct shmmap_state *shmmap_s;
	vm_offset_t attach_va;
	vm_prot_t prot;
	vm_size_t size;
	int cow, error, find_space, i, rv;

	AUDIT_ARG_SVIPC_ID(shmid);
	AUDIT_ARG_VALUE(shmflg);

	SYSVSHM_ASSERT_LOCKED();
	rpr = shm_find_prison(td->td_ucred);
	if (rpr == NULL)
		return (ENOSYS);
	shmmap_s = p->p_vmspace->vm_shm;
	if (shmmap_s == NULL) {
		shmmap_s = malloc(shminfo.shmseg * sizeof(struct shmmap_state),
		    M_SHM, M_WAITOK);
		for (i = 0; i < shminfo.shmseg; i++)
			shmmap_s[i].shmid = -1;
		KASSERT(p->p_vmspace->vm_shm == NULL, ("raced"));
		p->p_vmspace->vm_shm = shmmap_s;
	}
	shmseg = shm_find_segment(rpr, shmid, true);
	if (shmseg == NULL)
		return (EINVAL);
	error = ipcperm(td, &shmseg->u.shm_perm,
	    (shmflg & SHM_RDONLY) ? IPC_R : IPC_R|IPC_W);
	if (error != 0)
		return (error);
#ifdef MAC
	error = mac_sysvshm_check_shmat(td->td_ucred, shmseg, shmflg);
	if (error != 0)
		return (error);
#endif
	for (i = 0; i < shminfo.shmseg; i++) {
		if (shmmap_s->shmid == -1)
			break;
		shmmap_s++;
	}
	if (i >= shminfo.shmseg)
		return (EMFILE);
	size = round_page(shmseg->u.shm_segsz);
	prot = VM_PROT_READ;
	cow = MAP_INHERIT_SHARE | MAP_PREFAULT_PARTIAL;
	if ((shmflg & SHM_RDONLY) == 0)
		prot |= VM_PROT_WRITE;
	if (shmaddr != NULL) {
		if ((shmflg & SHM_RND) != 0)
			attach_va = rounddown2((vm_offset_t)shmaddr, SHMLBA);
		else if (((vm_offset_t)shmaddr & (SHMLBA-1)) == 0)
			attach_va = (vm_offset_t)shmaddr;
		else
			return (EINVAL);
		if ((shmflg & SHM_REMAP) != 0)
			cow |= MAP_REMAP;
		find_space = VMFS_NO_SPACE;
	} else {
		/*
		 * This is just a hint to vm_map_find() about where to
		 * put it.
		 */
		attach_va = round_page((vm_offset_t)p->p_vmspace->vm_daddr +
		    lim_max(td, RLIMIT_DATA));
		find_space = VMFS_OPTIMAL_SPACE;
	}

	vm_object_reference(shmseg->object);
	rv = vm_map_find(&p->p_vmspace->vm_map, shmseg->object, 0, &attach_va,
	    size, 0, find_space, prot, prot, cow);
	if (rv != KERN_SUCCESS) {
		vm_object_deallocate(shmseg->object);
		return (ENOMEM);
	}

	shmmap_s->va = attach_va;
	shmmap_s->shmid = shmid;
	shmseg->u.shm_lpid = p->p_pid;
	shmseg->u.shm_atime = time_second;
	shmseg->u.shm_nattch++;
	td->td_retval[0] = attach_va;
	return (error);
}