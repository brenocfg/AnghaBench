#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uia ;
typedef  int /*<<< orphan*/  ua ;
struct thread {TYPE_2__* td_proc; } ;
struct sparc_utrap_install_args {int num; char* handlers; int type; scalar_t__ new_precise; int /*<<< orphan*/ * old_precise; int /*<<< orphan*/ * old_deferred; } ;
struct sparc_utrap_args {int num; char* handlers; int type; scalar_t__ new_precise; int /*<<< orphan*/ * old_precise; int /*<<< orphan*/ * old_deferred; } ;
struct md_utrap {scalar_t__* ut_precise; } ;
struct TYPE_3__ {struct md_utrap* md_utrap; } ;
struct TYPE_4__ {TYPE_1__ p_md; } ;

/* Variables and functions */
 int EINVAL ; 
 int UTH_NOCHANGE ; 
 int UT_MAX ; 
 int copyin (char*,struct sparc_utrap_install_args*,int) ; 
 int suword (int /*<<< orphan*/ *,long) ; 
 struct md_utrap* utrap_alloc () ; 

__attribute__((used)) static int
sparc_utrap_install(struct thread *td, char *args)
{
	struct sparc_utrap_install_args uia;
	struct sparc_utrap_args ua;
	struct md_utrap *ut;
	int error;
	int i;

	ut = td->td_proc->p_md.md_utrap;
	if ((error = copyin(args, &uia, sizeof(uia))) != 0)
		return (error);
	if (uia.num < 0 || uia.num > UT_MAX ||
	    (uia.handlers == NULL && uia.num > 0))
		return (EINVAL);
	for (i = 0; i < uia.num; i++) {
		if ((error = copyin(&uia.handlers[i], &ua, sizeof(ua))) != 0)
			return (error);
		if (ua.type != UTH_NOCHANGE &&
		    (ua.type < 0 || ua.type >= UT_MAX))
			return (EINVAL);
		if (ua.old_deferred != NULL) {
			if ((error = suword(ua.old_deferred, 0)) != 0)
				return (error);
		}
		if (ua.old_precise != NULL) {
			error = suword(ua.old_precise,
			    ut != NULL ? (long)ut->ut_precise[ua.type] : 0);
			if (error != 0)
				return (error);
		}
		if (ua.type != UTH_NOCHANGE) {
			if (ut == NULL) {
				ut = utrap_alloc();
				td->td_proc->p_md.md_utrap = ut;
			}
			ut->ut_precise[ua.type] = ua.new_precise;
		}
	}
	return (0);
}