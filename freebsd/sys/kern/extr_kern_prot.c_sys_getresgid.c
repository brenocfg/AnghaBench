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
struct ucred {int /*<<< orphan*/  cr_svgid; int /*<<< orphan*/ * cr_groups; int /*<<< orphan*/  cr_rgid; } ;
struct thread {struct ucred* td_ucred; } ;
struct getresgid_args {int /*<<< orphan*/  sgid; int /*<<< orphan*/  egid; int /*<<< orphan*/  rgid; } ;

/* Variables and functions */
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
sys_getresgid(struct thread *td, struct getresgid_args *uap)
{
	struct ucred *cred;
	int error1 = 0, error2 = 0, error3 = 0;

	cred = td->td_ucred;
	if (uap->rgid)
		error1 = copyout(&cred->cr_rgid,
		    uap->rgid, sizeof(cred->cr_rgid));
	if (uap->egid)
		error2 = copyout(&cred->cr_groups[0],
		    uap->egid, sizeof(cred->cr_groups[0]));
	if (uap->sgid)
		error3 = copyout(&cred->cr_svgid,
		    uap->sgid, sizeof(cred->cr_svgid));
	return (error1 ? error1 : error2 ? error2 : error3);
}