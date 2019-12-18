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
typedef  int /*<<< orphan*/  val ;
struct thread {int dummy; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  id_t ;

/* Variables and functions */
 int EINVAL ; 
 int PGET_CANSEE ; 
 int PGET_NOTID ; 
 int PGET_NOTWEXIT ; 
 int /*<<< orphan*/  PRIV_IO ; 
#define  PROC_KPTI_CTL 129 
 int PROC_KPTI_CTL_DISABLE_ON_EXEC ; 
 int PROC_KPTI_CTL_ENABLE_ON_EXEC ; 
#define  PROC_KPTI_STATUS 128 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_PID ; 
 int copyin (void*,int*,int) ; 
 int copyout (int*,void*,int) ; 
 int /*<<< orphan*/  cpu_procctl_kpti (struct proc*,int,int*) ; 
 int pget (int /*<<< orphan*/ ,int,struct proc**) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 

int
cpu_procctl(struct thread *td, int idtype, id_t id, int com, void *data)
{
	struct proc *p;
	int error, val;

	switch (com) {
	case PROC_KPTI_CTL:
	case PROC_KPTI_STATUS:
		if (idtype != P_PID) {
			error = EINVAL;
			break;
		}
		if (com == PROC_KPTI_CTL) {
			/* sad but true and not a joke */
			error = priv_check(td, PRIV_IO);
			if (error != 0)
				break;
			error = copyin(data, &val, sizeof(val));
			if (error != 0)
				break;
			if (val != PROC_KPTI_CTL_ENABLE_ON_EXEC &&
			    val != PROC_KPTI_CTL_DISABLE_ON_EXEC) {
				error = EINVAL;
				break;
			}
		}
		error = pget(id, PGET_CANSEE | PGET_NOTWEXIT | PGET_NOTID, &p);
		if (error == 0) {
			cpu_procctl_kpti(p, com, &val);
			PROC_UNLOCK(p);
			if (com == PROC_KPTI_STATUS)
				error = copyout(&val, data, sizeof(val));
		}
		break;
	default:
		error = EINVAL;
		break;
	}
	return (error);
}