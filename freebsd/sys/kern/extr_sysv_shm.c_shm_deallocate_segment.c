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
typedef  int vm_size_t ;
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {TYPE_1__ shm_perm; int /*<<< orphan*/  shm_segsz; } ;
struct shmid_kernel {int /*<<< orphan*/ * cred; TYPE_2__ u; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int /*<<< orphan*/  RACCT_NSHM ; 
 int /*<<< orphan*/  RACCT_SHMSIZE ; 
 int /*<<< orphan*/  SHMSEG_FREE ; 
 int /*<<< orphan*/  SYSVSHM_ASSERT_LOCKED () ; 
 scalar_t__ btoc (int) ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mac_sysvshm_cleanup (struct shmid_kernel*) ; 
 int /*<<< orphan*/  racct_sub_cred (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int round_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_committed ; 
 int /*<<< orphan*/  shm_nused ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
shm_deallocate_segment(struct shmid_kernel *shmseg)
{
	vm_size_t size;

	SYSVSHM_ASSERT_LOCKED();

	vm_object_deallocate(shmseg->object);
	shmseg->object = NULL;
	size = round_page(shmseg->u.shm_segsz);
	shm_committed -= btoc(size);
	shm_nused--;
	shmseg->u.shm_perm.mode = SHMSEG_FREE;
#ifdef MAC
	mac_sysvshm_cleanup(shmseg);
#endif
	racct_sub_cred(shmseg->cred, RACCT_NSHM, 1);
	racct_sub_cred(shmseg->cred, RACCT_SHMSIZE, size);
	crfree(shmseg->cred);
	shmseg->cred = NULL;
}