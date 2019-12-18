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
typedef  int /*<<< orphan*/  mib ;
struct TYPE_3__ {int dwNumberOfProcessors; } ;
typedef  TYPE_1__ SYSTEM_INFO ;

/* Variables and functions */
 int CTL_HW ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_1__*) ; 
 int HW_NCPU ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
system_ncpus(void)
{
	int ncpus;
#if defined (__FreeBSD__)
	int mib[2] = { CTL_HW, HW_NCPU };
	size_t len = sizeof(mib);
	sysctl(mib, 2, &ncpus, &len, NULL, 0);
#elif defined(linux)
	ncpus = sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(_WIN32)
	{
		SYSTEM_INFO sysinfo;
		GetSystemInfo(&sysinfo);
		ncpus = sysinfo.dwNumberOfProcessors;
	}
#else /* others */
	ncpus = 1;
#endif /* others */
	return (ncpus);
}