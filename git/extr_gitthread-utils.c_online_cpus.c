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

/* Variables and functions */

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