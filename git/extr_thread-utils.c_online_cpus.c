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
struct pst_dynamic {scalar_t__ psd_proc_cnt; } ;
typedef  int /*<<< orphan*/  psd ;
typedef  int /*<<< orphan*/  cpucount ;
struct TYPE_3__ {scalar_t__ dwNumberOfProcessors; } ;
typedef  TYPE_1__ SYSTEM_INFO ;

/* Variables and functions */
 int CTL_HW ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 int HW_AVAILCPU ; 
 int HW_NCPU ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  pstat_getdynamic (struct pst_dynamic*,int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int online_cpus(void)
{
#ifdef NO_PTHREADS
	return 1;
#else
#ifdef _SC_NPROCESSORS_ONLN
	long ncpus;
#endif

#ifdef GIT_WINDOWS_NATIVE
	SYSTEM_INFO info;
	GetSystemInfo(&info);

	if ((int)info.dwNumberOfProcessors > 0)
		return (int)info.dwNumberOfProcessors;
#elif defined(hpux) || defined(__hpux) || defined(_hpux)
	struct pst_dynamic psd;

	if (!pstat_getdynamic(&psd, sizeof(psd), (size_t)1, 0))
		return (int)psd.psd_proc_cnt;
#elif defined(HAVE_BSD_SYSCTL) && defined(HW_NCPU)
	int mib[2];
	size_t len;
	int cpucount;

	mib[0] = CTL_HW;
#  ifdef HW_AVAILCPU
	mib[1] = HW_AVAILCPU;
	len = sizeof(cpucount);
	if (!sysctl(mib, 2, &cpucount, &len, NULL, 0))
		return cpucount;
#  endif /* HW_AVAILCPU */
	mib[1] = HW_NCPU;
	len = sizeof(cpucount);
	if (!sysctl(mib, 2, &cpucount, &len, NULL, 0))
		return cpucount;
#endif /* defined(HAVE_BSD_SYSCTL) && defined(HW_NCPU) */

#ifdef _SC_NPROCESSORS_ONLN
	if ((ncpus = (long)sysconf(_SC_NPROCESSORS_ONLN)) > 0)
		return (int)ncpus;
#endif

	return 1;
#endif
}