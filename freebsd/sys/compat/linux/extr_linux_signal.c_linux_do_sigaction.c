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
struct sigaction {int dummy; } ;
typedef  int /*<<< orphan*/  l_sigaction_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LINUX_SIG_VALID (int) ; 
 int /*<<< orphan*/  bsd_to_linux_sigaction (struct sigaction*,int /*<<< orphan*/ *) ; 
 int kern_sigaction (struct thread*,int,struct sigaction*,struct sigaction*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linux_to_bsd_sigaction (int /*<<< orphan*/ *,struct sigaction*) ; 
 int linux_to_bsd_signal (int) ; 

int
linux_do_sigaction(struct thread *td, int linux_sig, l_sigaction_t *linux_nsa,
		   l_sigaction_t *linux_osa)
{
	struct sigaction act, oact, *nsa, *osa;
	int error, sig;

	if (!LINUX_SIG_VALID(linux_sig))
		return (EINVAL);

	osa = (linux_osa != NULL) ? &oact : NULL;
	if (linux_nsa != NULL) {
		nsa = &act;
		linux_to_bsd_sigaction(linux_nsa, nsa);
	} else
		nsa = NULL;
	sig = linux_to_bsd_signal(linux_sig);

	error = kern_sigaction(td, sig, nsa, osa, 0);
	if (error)
		return (error);

	if (linux_osa != NULL)
		bsd_to_linux_sigaction(osa, linux_osa);

	return (0);
}