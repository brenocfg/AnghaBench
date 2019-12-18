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
struct linux_ptrace_args {int req; int data; scalar_t__ addr; scalar_t__ pid; } ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int EINVAL ; 
#define  LINUX_PTRACE_ATTACH 146 
#define  LINUX_PTRACE_CONT 145 
#define  LINUX_PTRACE_DETACH 144 
#define  LINUX_PTRACE_GETREGS 143 
#define  LINUX_PTRACE_GETREGSET 142 
#define  LINUX_PTRACE_GETSIGINFO 141 
#define  LINUX_PTRACE_KILL 140 
#define  LINUX_PTRACE_PEEKDATA 139 
#define  LINUX_PTRACE_PEEKTEXT 138 
#define  LINUX_PTRACE_PEEKUSER 137 
#define  LINUX_PTRACE_POKEDATA 136 
#define  LINUX_PTRACE_POKETEXT 135 
#define  LINUX_PTRACE_POKEUSER 134 
#define  LINUX_PTRACE_SEIZE 133 
#define  LINUX_PTRACE_SETOPTIONS 132 
#define  LINUX_PTRACE_SETREGS 131 
#define  LINUX_PTRACE_SINGLESTEP 130 
#define  LINUX_PTRACE_SYSCALL 129 
#define  LINUX_PTRACE_TRACEME 128 
 int /*<<< orphan*/  PT_ATTACH ; 
 int /*<<< orphan*/  PT_CONTINUE ; 
 int /*<<< orphan*/  PT_DETACH ; 
 int /*<<< orphan*/  PT_KILL ; 
 int /*<<< orphan*/  PT_STEP ; 
 int /*<<< orphan*/  PT_SYSCALL ; 
 int /*<<< orphan*/  PT_TRACE_ME ; 
 int /*<<< orphan*/  PT_WRITE_D ; 
 int /*<<< orphan*/  PT_WRITE_I ; 
 int kern_ptrace (struct thread*,int /*<<< orphan*/ ,scalar_t__,void*,int) ; 
 int /*<<< orphan*/  linux_msg (struct thread*,char*,int) ; 
 int linux_ptrace_getregs (struct thread*,scalar_t__,void*) ; 
 int linux_ptrace_getregset (struct thread*,scalar_t__,scalar_t__,int) ; 
 int linux_ptrace_getsiginfo (struct thread*,scalar_t__,int) ; 
 int linux_ptrace_peek (struct thread*,scalar_t__,void*,void*) ; 
 int linux_ptrace_peekuser (struct thread*,scalar_t__,void*,void*) ; 
 int linux_ptrace_pokeuser (struct thread*,scalar_t__,void*,void*) ; 
 int linux_ptrace_seize (struct thread*,scalar_t__,scalar_t__,int) ; 
 int linux_ptrace_setoptions (struct thread*,scalar_t__,int) ; 
 int linux_ptrace_setregs (struct thread*,scalar_t__,void*) ; 
 int map_signum (int,int*) ; 

int
linux_ptrace(struct thread *td, struct linux_ptrace_args *uap)
{
	void *addr;
	pid_t pid;
	int error, sig;

	pid  = (pid_t)uap->pid;
	addr = (void *)uap->addr;

	switch (uap->req) {
	case LINUX_PTRACE_TRACEME:
		error = kern_ptrace(td, PT_TRACE_ME, 0, 0, 0);
		break;
	case LINUX_PTRACE_PEEKTEXT:
	case LINUX_PTRACE_PEEKDATA:
		error = linux_ptrace_peek(td, pid, addr, (void *)uap->data);
		if (error != 0)
			return (error);
		/*
		 * Linux expects this syscall to read 64 bits, not 32.
		 */
		error = linux_ptrace_peek(td, pid,
		    (void *)(uap->addr + 4), (void *)(uap->data + 4));
		break;
	case LINUX_PTRACE_PEEKUSER:
		error = linux_ptrace_peekuser(td, pid, addr, (void *)uap->data);
		break;
	case LINUX_PTRACE_POKETEXT:
		error = kern_ptrace(td, PT_WRITE_I, pid, addr, uap->data);
		break;
	case LINUX_PTRACE_POKEDATA:
		error = kern_ptrace(td, PT_WRITE_D, pid, addr, uap->data);
		break;
	case LINUX_PTRACE_POKEUSER:
		error = linux_ptrace_pokeuser(td, pid, addr, (void *)uap->data);
		break;
	case LINUX_PTRACE_CONT:
		error = map_signum(uap->data, &sig);
		if (error != 0)
			break;
		error = kern_ptrace(td, PT_CONTINUE, pid, (void *)1, sig);
		break;
	case LINUX_PTRACE_KILL:
		error = kern_ptrace(td, PT_KILL, pid, addr, uap->data);
		break;
	case LINUX_PTRACE_SINGLESTEP:
		error = map_signum(uap->data, &sig);
		if (error != 0)
			break;
		error = kern_ptrace(td, PT_STEP, pid, (void *)1, sig);
		break;
	case LINUX_PTRACE_GETREGS:
		error = linux_ptrace_getregs(td, pid, (void *)uap->data);
		break;
	case LINUX_PTRACE_SETREGS:
		error = linux_ptrace_setregs(td, pid, (void *)uap->data);
		break;
	case LINUX_PTRACE_ATTACH:
		error = kern_ptrace(td, PT_ATTACH, pid, addr, uap->data);
		break;
	case LINUX_PTRACE_DETACH:
		error = map_signum(uap->data, &sig);
		if (error != 0)
			break;
		error = kern_ptrace(td, PT_DETACH, pid, (void *)1, sig);
		break;
	case LINUX_PTRACE_SYSCALL:
		error = map_signum(uap->data, &sig);
		if (error != 0)
			break;
		error = kern_ptrace(td, PT_SYSCALL, pid, (void *)1, sig);
		break;
	case LINUX_PTRACE_SETOPTIONS:
		error = linux_ptrace_setoptions(td, pid, uap->data);
		break;
	case LINUX_PTRACE_GETSIGINFO:
		error = linux_ptrace_getsiginfo(td, pid, uap->data);
		break;
	case LINUX_PTRACE_GETREGSET:
		error = linux_ptrace_getregset(td, pid, uap->addr, uap->data);
		break;
	case LINUX_PTRACE_SEIZE:
		error = linux_ptrace_seize(td, pid, uap->addr, uap->data);
		break;
	default:
		linux_msg(td, "ptrace(%ld, ...) not implemented; "
		    "returning EINVAL", uap->req);
		error = EINVAL;
		break;
	}

	return (error);
}