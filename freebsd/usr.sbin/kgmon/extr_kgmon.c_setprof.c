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
typedef  int /*<<< orphan*/  u_long ;
struct kvmvars {int /*<<< orphan*/  kd; } ;
struct gmonparam {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  state ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {scalar_t__ n_value; } ;

/* Variables and functions */
 int CTL_KERN ; 
 int GMON_PROF_OFF ; 
 int GPROF_STATE ; 
 int KERN_PROF ; 
 size_t N_GMONPARAM ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  kflag ; 
 scalar_t__ kvm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 TYPE_1__* nl ; 
 int /*<<< orphan*/  seteuid (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int*,int,int*,size_t*,int*,size_t) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

void
setprof(struct kvmvars *kvp, int state)
{
	struct gmonparam *p = (struct gmonparam *)nl[N_GMONPARAM].n_value;
	size_t sz;
	int mib[3], oldstate;

	sz = sizeof(state);
	if (!kflag) {
		mib[0] = CTL_KERN;
		mib[1] = KERN_PROF;
		mib[2] = GPROF_STATE;
		if (sysctl(mib, 3, &oldstate, &sz, NULL, 0) < 0)
			goto bad;
		if (oldstate == state)
			return;
		(void)seteuid(0);
		if (sysctl(mib, 3, NULL, NULL, &state, sz) >= 0) {
			(void)seteuid(getuid());
			return;
		}
		(void)seteuid(getuid());
	} else if (kvm_write(kvp->kd, (u_long)&p->state, (void *)&state, sz)
	    == (ssize_t)sz)
		return;
bad:
	warnx("warning: cannot turn profiling %s",
	    state == GMON_PROF_OFF ? "off" : "on");
}