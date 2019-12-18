#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kvmvars {int /*<<< orphan*/ * kd; } ;
struct TYPE_3__ {int /*<<< orphan*/  n_value; } ;

/* Variables and functions */
 scalar_t__ Bflag ; 
 int CTL_KERN ; 
 int GMON_PROF_HIRES ; 
 int GMON_PROF_ON ; 
 int GPROF_STATE ; 
 int KERN_PROF ; 
 size_t N_GMONPARAM ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int _POSIX2_LINE_MAX ; 
 scalar_t__ bflag ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  getuid () ; 
 scalar_t__ hflag ; 
 int /*<<< orphan*/  kern_readonly (int) ; 
 int /*<<< orphan*/  kflag ; 
 scalar_t__ kvm_nlist (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* kvm_openfiles (char const*,char*,int /*<<< orphan*/ *,int,char*) ; 
 TYPE_1__* nl ; 
 scalar_t__ pflag ; 
 scalar_t__ rflag ; 
 int /*<<< orphan*/  seteuid (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int*,int,int*,size_t*,int*,size_t) ; 

int
openfiles(const char *systemname, char *kmemf, struct kvmvars *kvp)
{
	size_t size;
	int mib[3], state, openmode;
	char errbuf[_POSIX2_LINE_MAX];

	if (!kflag) {
		mib[0] = CTL_KERN;
		mib[1] = KERN_PROF;
		mib[2] = GPROF_STATE;
		size = sizeof state;
		if (sysctl(mib, 3, &state, &size, NULL, 0) < 0)
			errx(20, "profiling not defined in kernel");
		if (!(Bflag || bflag || hflag || rflag ||
		    (pflag &&
		     (state == GMON_PROF_HIRES || state == GMON_PROF_ON))))
			return (O_RDONLY);
		(void)seteuid(0);
		if (sysctl(mib, 3, NULL, NULL, &state, size) >= 0)
			return (O_RDWR);
		(void)seteuid(getuid());
		kern_readonly(state);
		return (O_RDONLY);
	}
	openmode = (Bflag || bflag || hflag || pflag || rflag)
		   ? O_RDWR : O_RDONLY;
	kvp->kd = kvm_openfiles(systemname, kmemf, NULL, openmode, errbuf);
	if (kvp->kd == NULL) {
		if (openmode == O_RDWR) {
			openmode = O_RDONLY;
			kvp->kd = kvm_openfiles(systemname, kmemf, NULL, O_RDONLY,
			    errbuf);
		}
		if (kvp->kd == NULL)
			errx(2, "kvm_openfiles: %s", errbuf);
		kern_readonly(GMON_PROF_ON);
	}
	if (kvm_nlist(kvp->kd, nl) < 0)
		errx(3, "%s: no namelist", systemname);
	if (!nl[N_GMONPARAM].n_value)
		errx(20, "profiling not defined in kernel");
	return (openmode);
}