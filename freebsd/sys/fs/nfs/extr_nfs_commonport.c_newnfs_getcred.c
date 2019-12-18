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
struct ucred {int dummy; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;

/* Variables and functions */
 struct ucred* crdup (int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  newnfs_setroot (struct ucred*) ; 

struct ucred *
newnfs_getcred(void)
{
	struct ucred *cred;
	struct thread *td = curthread;

	cred = crdup(td->td_ucred);
	newnfs_setroot(cred);
	return (cred);
}