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
struct TYPE_3__ {int mode; scalar_t__ seq; } ;
struct TYPE_4__ {TYPE_1__ sem_perm; } ;
struct semid_kernel {TYPE_2__ u; } ;
struct prison {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IPCID_TO_SEQ (int) ; 
 int SEM_ALLOC ; 
 scalar_t__ sem_prison_cansee (struct prison*,struct semid_kernel*) ; 

__attribute__((used)) static int
semvalid(int semid, struct prison *rpr, struct semid_kernel *semakptr)
{

	return ((semakptr->u.sem_perm.mode & SEM_ALLOC) == 0 ||
	    semakptr->u.sem_perm.seq != IPCID_TO_SEQ(semid) ||
	    sem_prison_cansee(rpr, semakptr) ? EINVAL : 0);
}