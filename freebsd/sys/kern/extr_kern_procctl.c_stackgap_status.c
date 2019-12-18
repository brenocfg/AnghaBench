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
 int /*<<< orphan*/  MA_OWNED ; 
 int P2_STKGAP_DISABLE ; 
 int P2_STKGAP_DISABLE_EXEC ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int PROC_STACKGAP_DISABLE ; 
 int PROC_STACKGAP_DISABLE_EXEC ; 
 int PROC_STACKGAP_ENABLE ; 
 int PROC_STACKGAP_ENABLE_EXEC ; 

__attribute__((used)) static int
stackgap_status(struct thread *td, struct proc *p, int *data)
{
	PROC_LOCK_ASSERT(p, MA_OWNED);

	*data = (p->p_flag2 & P2_STKGAP_DISABLE) != 0 ? PROC_STACKGAP_DISABLE :
	    PROC_STACKGAP_ENABLE;
	*data |= (p->p_flag2 & P2_STKGAP_DISABLE_EXEC) != 0 ?
	    PROC_STACKGAP_DISABLE_EXEC : PROC_STACKGAP_ENABLE_EXEC;
	return (0);
}