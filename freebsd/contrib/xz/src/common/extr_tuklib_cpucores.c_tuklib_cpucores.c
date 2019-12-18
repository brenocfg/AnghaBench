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
typedef  int uint32_t ;
struct pst_dynamic {int psd_proc_cnt; } ;
typedef  int /*<<< orphan*/  set ;
typedef  int /*<<< orphan*/  pst ;
typedef  int /*<<< orphan*/  cpuset_t ;
typedef  int /*<<< orphan*/  cpus ;
typedef  int /*<<< orphan*/  cpu_set_t ;
typedef  int /*<<< orphan*/  cpu_mask ;
struct TYPE_3__ {int dwNumberOfProcessors; } ;
typedef  TYPE_1__ SYSTEM_INFO ;

/* Variables and functions */
 int CPU_COUNT (int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_ISSET (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_LEVEL_WHICH ; 
 unsigned int CPU_SETSIZE ; 
 int /*<<< orphan*/  CPU_WHICH_PID ; 
 int CTL_HW ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 int HW_NCPU ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  _SC_NPROC_ONLN ; 
 scalar_t__ cpuset_getaffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int pstat_getdynamic (struct pst_dynamic*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sched_getaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 long sysconf (int /*<<< orphan*/ ) ; 
 int sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

extern uint32_t
tuklib_cpucores(void)
{
	uint32_t ret = 0;

#if defined(_WIN32) || defined(__CYGWIN__)
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	ret = sysinfo.dwNumberOfProcessors;

#elif defined(TUKLIB_CPUCORES_SCHED_GETAFFINITY)
	cpu_set_t cpu_mask;
	if (sched_getaffinity(0, sizeof(cpu_mask), &cpu_mask) == 0)
		ret = CPU_COUNT(&cpu_mask);

#elif defined(TUKLIB_CPUCORES_CPUSET)
	cpuset_t set;
	if (cpuset_getaffinity(CPU_LEVEL_WHICH, CPU_WHICH_PID, -1,
			sizeof(set), &set) == 0) {
#	ifdef CPU_COUNT
		ret = CPU_COUNT(&set);
#	else
		for (unsigned i = 0; i < CPU_SETSIZE; ++i)
			if (CPU_ISSET(i, &set))
				++ret;
#	endif
	}

#elif defined(TUKLIB_CPUCORES_SYSCTL)
	int name[2] = { CTL_HW, HW_NCPU };
	int cpus;
	size_t cpus_size = sizeof(cpus);
	if (sysctl(name, 2, &cpus, &cpus_size, NULL, 0) != -1
			&& cpus_size == sizeof(cpus) && cpus > 0)
		ret = cpus;

#elif defined(TUKLIB_CPUCORES_SYSCONF)
#	ifdef _SC_NPROCESSORS_ONLN
	// Most systems
	const long cpus = sysconf(_SC_NPROCESSORS_ONLN);
#	else
	// IRIX
	const long cpus = sysconf(_SC_NPROC_ONLN);
#	endif
	if (cpus > 0)
		ret = cpus;

#elif defined(TUKLIB_CPUCORES_PSTAT_GETDYNAMIC)
	struct pst_dynamic pst;
	if (pstat_getdynamic(&pst, sizeof(pst), 1, 0) != -1)
		ret = pst.psd_proc_cnt;
#endif

	return ret;
}