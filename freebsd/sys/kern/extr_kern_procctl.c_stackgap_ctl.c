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
struct thread {int dummy; } ;
struct proc {int p_flag2; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int P2_STKGAP_DISABLE ; 
 int P2_STKGAP_DISABLE_EXEC ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
#define  PROC_STACKGAP_DISABLE 131 
#define  PROC_STACKGAP_DISABLE_EXEC 130 
#define  PROC_STACKGAP_ENABLE 129 
#define  PROC_STACKGAP_ENABLE_EXEC 128 

__attribute__((used)) static int
stackgap_ctl(struct thread *td, struct proc *p, int state)
{
	PROC_LOCK_ASSERT(p, MA_OWNED);

	if ((state & ~(PROC_STACKGAP_ENABLE | PROC_STACKGAP_DISABLE |
	    PROC_STACKGAP_ENABLE_EXEC | PROC_STACKGAP_DISABLE_EXEC)) != 0)
		return (EINVAL);
	switch (state & (PROC_STACKGAP_ENABLE | PROC_STACKGAP_DISABLE)) {
	case PROC_STACKGAP_ENABLE:
		if ((p->p_flag2 & P2_STKGAP_DISABLE) != 0)
			return (EINVAL);
		break;
	case PROC_STACKGAP_DISABLE:
		p->p_flag2 |= P2_STKGAP_DISABLE;
		break;
	case 0:
		break;
	default:
		return (EINVAL);
	}
	switch (state & (PROC_STACKGAP_ENABLE_EXEC |
	    PROC_STACKGAP_DISABLE_EXEC)) {
	case PROC_STACKGAP_ENABLE_EXEC:
		p->p_flag2 &= ~P2_STKGAP_DISABLE_EXEC;
		break;
	case PROC_STACKGAP_DISABLE_EXEC:
		p->p_flag2 |= P2_STKGAP_DISABLE_EXEC;
		break;
	case 0:
		break;
	default:
		return (EINVAL);
	}
	return (0);
}