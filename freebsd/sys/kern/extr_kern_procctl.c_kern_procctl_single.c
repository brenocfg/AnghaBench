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
struct proc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MA_OWNED ; 
#define  PROC_ASLR_CTL 143 
#define  PROC_ASLR_STATUS 142 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
#define  PROC_PROTMAX_CTL 141 
#define  PROC_PROTMAX_STATUS 140 
#define  PROC_REAP_ACQUIRE 139 
#define  PROC_REAP_GETPIDS 138 
#define  PROC_REAP_KILL 137 
#define  PROC_REAP_RELEASE 136 
#define  PROC_REAP_STATUS 135 
#define  PROC_SPROTECT 134 
#define  PROC_STACKGAP_CTL 133 
#define  PROC_STACKGAP_STATUS 132 
#define  PROC_TRACE_CTL 131 
#define  PROC_TRACE_STATUS 130 
#define  PROC_TRAPCAP_CTL 129 
#define  PROC_TRAPCAP_STATUS 128 
 int aslr_ctl (struct thread*,struct proc*,int) ; 
 int aslr_status (struct thread*,struct proc*,void*) ; 
 int protect_set (struct thread*,struct proc*,int) ; 
 int protmax_ctl (struct thread*,struct proc*,int) ; 
 int protmax_status (struct thread*,struct proc*,void*) ; 
 int reap_acquire (struct thread*,struct proc*) ; 
 int reap_getpids (struct thread*,struct proc*,void*) ; 
 int reap_kill (struct thread*,struct proc*,void*) ; 
 int reap_release (struct thread*,struct proc*) ; 
 int reap_status (struct thread*,struct proc*,void*) ; 
 int stackgap_ctl (struct thread*,struct proc*,int) ; 
 int stackgap_status (struct thread*,struct proc*,void*) ; 
 int trace_ctl (struct thread*,struct proc*,int) ; 
 int trace_status (struct thread*,struct proc*,void*) ; 
 int trapcap_ctl (struct thread*,struct proc*,int) ; 
 int trapcap_status (struct thread*,struct proc*,void*) ; 

__attribute__((used)) static int
kern_procctl_single(struct thread *td, struct proc *p, int com, void *data)
{

	PROC_LOCK_ASSERT(p, MA_OWNED);
	switch (com) {
	case PROC_ASLR_CTL:
		return (aslr_ctl(td, p, *(int *)data));
	case PROC_ASLR_STATUS:
		return (aslr_status(td, p, data));
	case PROC_SPROTECT:
		return (protect_set(td, p, *(int *)data));
	case PROC_PROTMAX_CTL:
		return (protmax_ctl(td, p, *(int *)data));
	case PROC_PROTMAX_STATUS:
		return (protmax_status(td, p, data));
	case PROC_STACKGAP_CTL:
		return (stackgap_ctl(td, p, *(int *)data));
	case PROC_STACKGAP_STATUS:
		return (stackgap_status(td, p, data));
	case PROC_REAP_ACQUIRE:
		return (reap_acquire(td, p));
	case PROC_REAP_RELEASE:
		return (reap_release(td, p));
	case PROC_REAP_STATUS:
		return (reap_status(td, p, data));
	case PROC_REAP_GETPIDS:
		return (reap_getpids(td, p, data));
	case PROC_REAP_KILL:
		return (reap_kill(td, p, data));
	case PROC_TRACE_CTL:
		return (trace_ctl(td, p, *(int *)data));
	case PROC_TRACE_STATUS:
		return (trace_status(td, p, data));
	case PROC_TRAPCAP_CTL:
		return (trapcap_ctl(td, p, *(int *)data));
	case PROC_TRAPCAP_STATUS:
		return (trapcap_status(td, p, data));
	default:
		return (EINVAL);
	}
}