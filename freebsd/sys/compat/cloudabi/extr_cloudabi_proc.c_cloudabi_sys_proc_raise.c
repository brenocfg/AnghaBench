#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* td_ucred; struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_pid; } ;
struct cloudabi_sys_proc_raise_args {size_t sig; } ;
struct TYPE_6__ {int ksi_signo; int /*<<< orphan*/  ksi_uid; int /*<<< orphan*/  ksi_pid; int /*<<< orphan*/  ksi_code; } ;
typedef  TYPE_2__ ksiginfo_t ;
struct TYPE_5__ {int /*<<< orphan*/  cr_ruid; } ;

/* Variables and functions */
#define  CLOUDABI_SIGABRT 179 
#define  CLOUDABI_SIGALRM 178 
#define  CLOUDABI_SIGBUS 177 
#define  CLOUDABI_SIGCHLD 176 
#define  CLOUDABI_SIGCONT 175 
#define  CLOUDABI_SIGFPE 174 
#define  CLOUDABI_SIGHUP 173 
#define  CLOUDABI_SIGILL 172 
#define  CLOUDABI_SIGINT 171 
#define  CLOUDABI_SIGKILL 170 
#define  CLOUDABI_SIGPIPE 169 
#define  CLOUDABI_SIGQUIT 168 
#define  CLOUDABI_SIGSEGV 167 
#define  CLOUDABI_SIGSTOP 166 
#define  CLOUDABI_SIGSYS 165 
#define  CLOUDABI_SIGTERM 164 
#define  CLOUDABI_SIGTRAP 163 
#define  CLOUDABI_SIGTSTP 162 
#define  CLOUDABI_SIGTTIN 161 
#define  CLOUDABI_SIGTTOU 160 
#define  CLOUDABI_SIGURG 159 
#define  CLOUDABI_SIGUSR1 158 
#define  CLOUDABI_SIGUSR2 157 
#define  CLOUDABI_SIGVTALRM 156 
#define  CLOUDABI_SIGXCPU 155 
#define  CLOUDABI_SIGXFSZ 154 
 int EINVAL ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
#define  SIGABRT 153 
#define  SIGALRM 152 
#define  SIGBUS 151 
#define  SIGCHLD 150 
#define  SIGCONT 149 
#define  SIGFPE 148 
#define  SIGHUP 147 
#define  SIGILL 146 
#define  SIGINT 145 
#define  SIGKILL 144 
#define  SIGPIPE 143 
#define  SIGQUIT 142 
#define  SIGSEGV 141 
#define  SIGSTOP 140 
#define  SIGSYS 139 
#define  SIGTERM 138 
#define  SIGTRAP 137 
#define  SIGTSTP 136 
#define  SIGTTIN 135 
#define  SIGTTOU 134 
#define  SIGURG 133 
#define  SIGUSR1 132 
#define  SIGUSR2 131 
#define  SIGVTALRM 130 
#define  SIGXCPU 129 
#define  SIGXFSZ 128 
 int /*<<< orphan*/  SI_USER ; 
 int /*<<< orphan*/  ksiginfo_init (TYPE_2__*) ; 
 size_t nitems (int const*) ; 
 int /*<<< orphan*/  pksignal (struct proc*,int,TYPE_2__*) ; 

int
cloudabi_sys_proc_raise(struct thread *td,
    struct cloudabi_sys_proc_raise_args *uap)
{
	static const int signals[] = {
		[CLOUDABI_SIGABRT] = SIGABRT,
		[CLOUDABI_SIGALRM] = SIGALRM,
		[CLOUDABI_SIGBUS] = SIGBUS,
		[CLOUDABI_SIGCHLD] = SIGCHLD,
		[CLOUDABI_SIGCONT] = SIGCONT,
		[CLOUDABI_SIGFPE] = SIGFPE,
		[CLOUDABI_SIGHUP] = SIGHUP,
		[CLOUDABI_SIGILL] = SIGILL,
		[CLOUDABI_SIGINT] = SIGINT,
		[CLOUDABI_SIGKILL] = SIGKILL,
		[CLOUDABI_SIGPIPE] = SIGPIPE,
		[CLOUDABI_SIGQUIT] = SIGQUIT,
		[CLOUDABI_SIGSEGV] = SIGSEGV,
		[CLOUDABI_SIGSTOP] = SIGSTOP,
		[CLOUDABI_SIGSYS] = SIGSYS,
		[CLOUDABI_SIGTERM] = SIGTERM,
		[CLOUDABI_SIGTRAP] = SIGTRAP,
		[CLOUDABI_SIGTSTP] = SIGTSTP,
		[CLOUDABI_SIGTTIN] = SIGTTIN,
		[CLOUDABI_SIGTTOU] = SIGTTOU,
		[CLOUDABI_SIGURG] = SIGURG,
		[CLOUDABI_SIGUSR1] = SIGUSR1,
		[CLOUDABI_SIGUSR2] = SIGUSR2,
		[CLOUDABI_SIGVTALRM] = SIGVTALRM,
		[CLOUDABI_SIGXCPU] = SIGXCPU,
		[CLOUDABI_SIGXFSZ] = SIGXFSZ,
	};
	ksiginfo_t ksi;
	struct proc *p;

	if (uap->sig >= nitems(signals) || signals[uap->sig] == 0) {
		/* Invalid signal, or the null signal. */
		return (uap->sig == 0 ? 0 : EINVAL);
	}

	p = td->td_proc;
	ksiginfo_init(&ksi);
	ksi.ksi_signo = signals[uap->sig];
	ksi.ksi_code = SI_USER;
	ksi.ksi_pid = p->p_pid;
	ksi.ksi_uid = td->td_ucred->cr_ruid;
	PROC_LOCK(p);
	pksignal(p, ksi.ksi_signo, &ksi);
	PROC_UNLOCK(p);
	return (0);
}