#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ucred {int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; } ;
struct shmfd {int /*<<< orphan*/  shm_rl; int /*<<< orphan*/  shm_mtx; int /*<<< orphan*/  shm_refs; int /*<<< orphan*/  shm_ino; int /*<<< orphan*/  shm_birthtime; int /*<<< orphan*/  shm_ctime; int /*<<< orphan*/  shm_mtime; int /*<<< orphan*/  shm_atime; TYPE_1__* shm_object; scalar_t__ shm_size; int /*<<< orphan*/  shm_mode; int /*<<< orphan*/  shm_gid; int /*<<< orphan*/  shm_uid; } ;
typedef  int /*<<< orphan*/  mode_t ;
struct TYPE_6__ {scalar_t__ pg_color; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_SHMFD ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OBJT_SWAP ; 
 int OBJ_COLORED ; 
 int OBJ_NOSPLIT ; 
 int /*<<< orphan*/  OBJ_ONEMAPPING ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_PROT_DEFAULT ; 
 int /*<<< orphan*/  alloc_unr64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_posixshm_create (struct ucred*,struct shmfd*) ; 
 int /*<<< orphan*/  mac_posixshm_init (struct shmfd*) ; 
 struct shmfd* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rangelock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  shm_ino_unr ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_clear_flag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_set_flag (TYPE_1__*,int) ; 
 TYPE_1__* vm_pager_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*) ; 

struct shmfd *
shm_alloc(struct ucred *ucred, mode_t mode)
{
	struct shmfd *shmfd;

	shmfd = malloc(sizeof(*shmfd), M_SHMFD, M_WAITOK | M_ZERO);
	shmfd->shm_size = 0;
	shmfd->shm_uid = ucred->cr_uid;
	shmfd->shm_gid = ucred->cr_gid;
	shmfd->shm_mode = mode;
	shmfd->shm_object = vm_pager_allocate(OBJT_SWAP, NULL,
	    shmfd->shm_size, VM_PROT_DEFAULT, 0, ucred);
	KASSERT(shmfd->shm_object != NULL, ("shm_create: vm_pager_allocate"));
	shmfd->shm_object->pg_color = 0;
	VM_OBJECT_WLOCK(shmfd->shm_object);
	vm_object_clear_flag(shmfd->shm_object, OBJ_ONEMAPPING);
	vm_object_set_flag(shmfd->shm_object, OBJ_COLORED | OBJ_NOSPLIT);
	VM_OBJECT_WUNLOCK(shmfd->shm_object);
	vfs_timestamp(&shmfd->shm_birthtime);
	shmfd->shm_atime = shmfd->shm_mtime = shmfd->shm_ctime =
	    shmfd->shm_birthtime;
	shmfd->shm_ino = alloc_unr64(&shm_ino_unr);
	refcount_init(&shmfd->shm_refs, 1);
	mtx_init(&shmfd->shm_mtx, "shmrl", NULL, MTX_DEF);
	rangelock_init(&shmfd->shm_rl);
#ifdef MAC
	mac_posixshm_init(shmfd);
	mac_posixshm_create(ucred, shmfd);
#endif

	return (shmfd);
}