#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct user_segment_descriptor {int num; int /*<<< orphan*/ * descs; } ;
struct thread {int /*<<< orphan*/  td_pcb; } ;
struct sysarch_args {int op; int /*<<< orphan*/ * parms; } ;
struct i386_ldt_args {int num; int /*<<< orphan*/ * descs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_CMD (int) ; 
 int EINVAL ; 
#define  I386_GET_LDT 129 
#define  I386_SET_LDT 128 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PCB_FULL_IRET ; 
 int UIO_USERSPACE ; 
 int amd64_get_ldt (struct thread*,struct user_segment_descriptor*) ; 
 int amd64_set_ldt (struct thread*,struct user_segment_descriptor*,struct user_segment_descriptor*) ; 
 int copyin (int /*<<< orphan*/ *,struct user_segment_descriptor*,int) ; 
 int /*<<< orphan*/  free (struct user_segment_descriptor*,int /*<<< orphan*/ ) ; 
 struct user_segment_descriptor* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int max_ldt_segment ; 
 int /*<<< orphan*/  set_pcb_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
sysarch_ldt(struct thread *td, struct sysarch_args *uap, int uap_space)
{
	struct i386_ldt_args *largs, la;
	struct user_segment_descriptor *lp;
	int error = 0;

	/*
	 * XXXKIB check that the BSM generation code knows to encode
	 * the op argument.
	 */
	AUDIT_ARG_CMD(uap->op);
	if (uap_space == UIO_USERSPACE) {
		error = copyin(uap->parms, &la, sizeof(struct i386_ldt_args));
		if (error != 0)
			return (error);
		largs = &la;
	} else
		largs = (struct i386_ldt_args *)uap->parms;

	switch (uap->op) {
	case I386_GET_LDT:
		error = amd64_get_ldt(td, largs);
		break;
	case I386_SET_LDT:
		if (largs->descs != NULL && largs->num > max_ldt_segment)
			return (EINVAL);
		set_pcb_flags(td->td_pcb, PCB_FULL_IRET);
		if (largs->descs != NULL) {
			lp = malloc(largs->num * sizeof(struct
			    user_segment_descriptor), M_TEMP, M_WAITOK);
			error = copyin(largs->descs, lp, largs->num *
			    sizeof(struct user_segment_descriptor));
			if (error == 0)
				error = amd64_set_ldt(td, largs, lp);
			free(lp, M_TEMP);
		} else {
			error = amd64_set_ldt(td, largs, NULL);
		}
		break;
	}
	return (error);
}