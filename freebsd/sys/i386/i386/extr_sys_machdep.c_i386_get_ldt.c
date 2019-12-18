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
typedef  union descriptor {int dummy; } descriptor ;
typedef  int u_int ;
struct thread {int* td_retval; TYPE_2__* td_proc; } ;
struct proc_ldt {int ldt_len; scalar_t__ ldt_base; } ;
struct i386_ldt_args {int start; int num; scalar_t__ descs; } ;
struct TYPE_3__ {struct proc_ldt* md_ldt; } ;
struct TYPE_4__ {TYPE_1__ p_md; } ;

/* Variables and functions */
 int MAX_LD ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NLDT ; 
 int /*<<< orphan*/  bcopy (union descriptor*,char*,int) ; 
 int copyout (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dt_lock ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 union descriptor* ldt ; 
 char* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int,void*) ; 

int
i386_get_ldt(struct thread *td, struct i386_ldt_args *uap)
{
	struct proc_ldt *pldt;
	char *data;
	u_int nldt, num;
	int error;

#ifdef DEBUG
	printf("i386_get_ldt: start=%u num=%u descs=%p\n",
	    uap->start, uap->num, (void *)uap->descs);
#endif

	num = min(uap->num, MAX_LD);
	data = malloc(num * sizeof(union descriptor), M_TEMP, M_WAITOK);
	mtx_lock_spin(&dt_lock);
	pldt = td->td_proc->p_md.md_ldt;
	nldt = pldt != NULL ? pldt->ldt_len : NLDT;
	if (uap->start >= nldt) {
		num = 0;
	} else {
		num = min(num, nldt - uap->start);
		bcopy(pldt != NULL ?
		    &((union descriptor *)(pldt->ldt_base))[uap->start] :
		    &ldt[uap->start], data, num * sizeof(union descriptor));
	}
	mtx_unlock_spin(&dt_lock);
	error = copyout(data, uap->descs, num * sizeof(union descriptor));
	if (error == 0)
		td->td_retval[0] = num;
	free(data, M_TEMP);
	return (error);
}