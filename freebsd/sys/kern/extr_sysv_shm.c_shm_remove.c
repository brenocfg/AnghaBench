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
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {scalar_t__ shm_nattch; TYPE_1__ shm_perm; } ;
struct shmid_kernel {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_PRIVATE ; 
 int /*<<< orphan*/  SHMSEG_REMOVED ; 
 int /*<<< orphan*/  shm_deallocate_segment (struct shmid_kernel*) ; 
 int shm_last_free ; 

__attribute__((used)) static void
shm_remove(struct shmid_kernel *shmseg, int segnum)
{

	shmseg->u.shm_perm.key = IPC_PRIVATE;
	shmseg->u.shm_perm.mode |= SHMSEG_REMOVED;
	if (shmseg->u.shm_nattch == 0) {
		shm_deallocate_segment(shmseg);
		shm_last_free = segnum;
	}
}