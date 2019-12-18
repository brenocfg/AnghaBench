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

/* Variables and functions */
 int SIGCONT ; 
 int SIGTSTP ; 
 void SIG_DFL (int) ; 
 int errno ; 
 int /*<<< orphan*/  gettty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  settty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int,void (*) (int)) ; 
 int /*<<< orphan*/  ttyedit ; 
 int /*<<< orphan*/  ttysaved ; 

void
tstpcont(int sig)
{
	int save_errno = errno;

	if (sig == SIGTSTP) {
		signal(SIGCONT, tstpcont);
		gettty(&ttyedit);
		settty(&ttysaved);		
	} else {
		signal(SIGTSTP, tstpcont);
		settty(&ttyedit);		
	}
	signal(sig, SIG_DFL);
	kill(0, sig);
	errno = save_errno;
}