#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct prison {int dummy; } ;
struct TYPE_8__ {int mode; } ;
struct TYPE_7__ {TYPE_3__ sem_perm; } ;
struct TYPE_10__ {TYPE_1__* cred; TYPE_2__ u; } ;
struct TYPE_9__ {int semmni; } ;
struct TYPE_6__ {struct prison* cr_prison; } ;

/* Variables and functions */
 int SEM_ALLOC ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_mtx ; 
 int /*<<< orphan*/  sem_remove (int,int /*<<< orphan*/ *) ; 
 TYPE_5__* sema ; 
 int /*<<< orphan*/ * sema_mtx ; 
 TYPE_4__ seminfo ; 

__attribute__((used)) static void
sem_prison_cleanup(struct prison *pr)
{
	int i;

	/* Remove any sems that belong to this jail. */
	mtx_lock(&sem_mtx);
	for (i = 0; i < seminfo.semmni; i++) {
		if ((sema[i].u.sem_perm.mode & SEM_ALLOC) &&
		    sema[i].cred != NULL && sema[i].cred->cr_prison == pr) {
			mtx_lock(&sema_mtx[i]);
			sem_remove(i, NULL);
			mtx_unlock(&sema_mtx[i]);
		}
	}
	mtx_unlock(&sem_mtx);
}