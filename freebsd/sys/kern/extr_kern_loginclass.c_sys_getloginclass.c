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
struct thread {TYPE_1__* td_ucred; } ;
struct loginclass {int /*<<< orphan*/  lc_name; } ;
struct getloginclass_args {size_t namelen; int /*<<< orphan*/  namebuf; } ;
struct TYPE_2__ {struct loginclass* cr_loginclass; } ;

/* Variables and functions */
 int ERANGE ; 
 int copyout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int
sys_getloginclass(struct thread *td, struct getloginclass_args *uap)
{
	struct loginclass *lc;
	size_t lcnamelen;

	lc = td->td_ucred->cr_loginclass;
	lcnamelen = strlen(lc->lc_name) + 1;
	if (lcnamelen > uap->namelen)
		return (ERANGE);
	return (copyout(lc->lc_name, uap->namebuf, lcnamelen));
}