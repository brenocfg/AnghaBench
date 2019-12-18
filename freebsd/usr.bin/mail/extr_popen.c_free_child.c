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
struct child {int free; scalar_t__ done; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  delchild (struct child*) ; 
 struct child* findchild (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
free_child(pid_t pid)
{
	struct child *cp;
	sigset_t nset, oset;

	(void)sigemptyset(&nset);
	(void)sigaddset(&nset, SIGCHLD);
	(void)sigprocmask(SIG_BLOCK, &nset, &oset);
	if ((cp = findchild(pid, 0)) != NULL) {
		if (cp->done)
			delchild(cp);
		else
			cp->free = 1;
	}
	(void)sigprocmask(SIG_SETMASK, &oset, NULL);
}