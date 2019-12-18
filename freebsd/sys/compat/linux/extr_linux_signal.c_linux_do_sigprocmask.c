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
struct thread {scalar_t__* td_retval; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  l_sigset_t ;

/* Variables and functions */
 int EINVAL ; 
#define  LINUX_SIG_BLOCK 130 
#define  LINUX_SIG_SETMASK 129 
#define  LINUX_SIG_UNBLOCK 128 
 int SIG_BLOCK ; 
 int SIG_SETMASK ; 
 int SIG_UNBLOCK ; 
 int /*<<< orphan*/  bsd_to_linux_sigset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int kern_sigprocmask (struct thread*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_to_bsd_sigset (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
linux_do_sigprocmask(struct thread *td, int how, l_sigset_t *new,
		     l_sigset_t *old)
{
	sigset_t omask, nmask;
	sigset_t *nmaskp;
	int error;

	td->td_retval[0] = 0;

	switch (how) {
	case LINUX_SIG_BLOCK:
		how = SIG_BLOCK;
		break;
	case LINUX_SIG_UNBLOCK:
		how = SIG_UNBLOCK;
		break;
	case LINUX_SIG_SETMASK:
		how = SIG_SETMASK;
		break;
	default:
		return (EINVAL);
	}
	if (new != NULL) {
		linux_to_bsd_sigset(new, &nmask);
		nmaskp = &nmask;
	} else
		nmaskp = NULL;
	error = kern_sigprocmask(td, how, nmaskp, &omask, 0);
	if (error == 0 && old != NULL)
		bsd_to_linux_sigset(&omask, old);

	return (error);
}