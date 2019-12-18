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
struct TYPE_4__ {int mode; } ;
struct TYPE_5__ {TYPE_1__ shm_perm; } ;
struct shmid_kernel {TYPE_3__* cred; TYPE_2__ u; } ;
struct prison {int dummy; } ;
struct TYPE_6__ {struct prison* cr_prison; } ;

/* Variables and functions */
 int SHMSEG_ALLOCATED ; 
 int /*<<< orphan*/  shm_remove (struct shmid_kernel*,int) ; 
 int shmalloced ; 
 struct shmid_kernel* shmsegs ; 

__attribute__((used)) static void
shm_prison_cleanup(struct prison *pr)
{
	struct shmid_kernel *shmseg;
	int i;

	/* Remove any segments that belong to this jail. */
	for (i = 0; i < shmalloced; i++) {
		shmseg = &shmsegs[i];
		if ((shmseg->u.shm_perm.mode & SHMSEG_ALLOCATED) &&
		    shmseg->cred != NULL && shmseg->cred->cr_prison == pr) {
			shm_remove(shmseg, i);
		}
	}
}