#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* td_proc; } ;
struct pmclog_proc_init_args {int /*<<< orphan*/  kthr; } ;
struct TYPE_2__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  RFHIGHPID ; 
 int kproc_create (int /*<<< orphan*/ ,struct pmclog_proc_init_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct pmclog_proc_init_args* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmclog_loop ; 

int
pmclog_proc_create(struct thread *td, void **handlep)
{
	struct pmclog_proc_init_args *ia;
	int error;

	ia = malloc(sizeof(*ia), M_TEMP, M_WAITOK | M_ZERO);
	error = kproc_create(pmclog_loop, ia, &ia->kthr,
	    RFHIGHPID, 0, "hwpmc: proc(%d)", td->td_proc->p_pid);
	if (error == 0)
		*handlep = ia;
	return (error);
}