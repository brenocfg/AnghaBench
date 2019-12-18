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
 int P2_ASLR_DISABLE ; 
 int P2_ASLR_ENABLE ; 
#define  PROC_ASLR_FORCE_DISABLE 130 
#define  PROC_ASLR_FORCE_ENABLE 129 
#define  PROC_ASLR_NOFORCE 128 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
aslr_ctl(struct thread *td, struct proc *p, int state)
{

	PROC_LOCK_ASSERT(p, MA_OWNED);

	switch (state) {
	case PROC_ASLR_FORCE_ENABLE:
		p->p_flag2 &= ~P2_ASLR_DISABLE;
		p->p_flag2 |= P2_ASLR_ENABLE;
		break;
	case PROC_ASLR_FORCE_DISABLE:
		p->p_flag2 |= P2_ASLR_DISABLE;
		p->p_flag2 &= ~P2_ASLR_ENABLE;
		break;
	case PROC_ASLR_NOFORCE:
		p->p_flag2 &= ~(P2_ASLR_ENABLE | P2_ASLR_DISABLE);
		break;
	default:
		return (EINVAL);
	}
	return (0);
}