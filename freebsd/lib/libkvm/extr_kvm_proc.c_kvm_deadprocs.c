#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct proc {int dummy; } ;
struct kinfo_proc {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  program; struct kinfo_proc* procbase; } ;
typedef  TYPE_1__ kvm_t ;

/* Variables and functions */
 scalar_t__ KREAD (TYPE_1__*,scalar_t__,struct proc**) ; 
 int /*<<< orphan*/  _kvm_err (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int kvm_proclist (TYPE_1__*,int,int,struct proc*,struct kinfo_proc*,int) ; 

__attribute__((used)) static int
kvm_deadprocs(kvm_t *kd, int what, int arg, u_long a_allproc,
    u_long a_zombproc, int maxcnt)
{
	struct kinfo_proc *bp = kd->procbase;
	int acnt, zcnt = 0;
	struct proc *p;

	if (KREAD(kd, a_allproc, &p)) {
		_kvm_err(kd, kd->program, "cannot read allproc");
		return (-1);
	}
	acnt = kvm_proclist(kd, what, arg, p, bp, maxcnt);
	if (acnt < 0)
		return (acnt);

	if (a_zombproc != 0) {
		if (KREAD(kd, a_zombproc, &p)) {
			_kvm_err(kd, kd->program, "cannot read zombproc");
			return (-1);
		}
		zcnt = kvm_proclist(kd, what, arg, p, bp + acnt, maxcnt - acnt);
		if (zcnt < 0)
			zcnt = 0;
	}

	return (acnt + zcnt);
}