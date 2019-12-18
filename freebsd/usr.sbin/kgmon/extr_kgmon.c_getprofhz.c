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
struct kvmvars {int /*<<< orphan*/  kd; } ;
struct clockinfo {int profhz; } ;
struct TYPE_2__ {int /*<<< orphan*/  n_value; } ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_CLOCKRATE ; 
 size_t N_PROFHZ ; 
 scalar_t__ kflag ; 
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ ) ; 
 int kvm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 TYPE_1__* nl ; 
 scalar_t__ sysctl (int*,int,struct clockinfo*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

int
getprofhz(struct kvmvars *kvp)
{
	size_t size;
	int mib[2], profrate;
	struct clockinfo clockrate;

	if (kflag) {
		profrate = 1;
		if (kvm_read(kvp->kd, nl[N_PROFHZ].n_value, &profrate,
		    sizeof profrate) != sizeof profrate)
			warnx("get clockrate: %s", kvm_geterr(kvp->kd));
		return (profrate);
	}
	mib[0] = CTL_KERN;
	mib[1] = KERN_CLOCKRATE;
	clockrate.profhz = 1;
	size = sizeof clockrate;
	if (sysctl(mib, 2, &clockrate, &size, NULL, 0) < 0)
		warn("get clockrate");
	return (clockrate.profhz);
}