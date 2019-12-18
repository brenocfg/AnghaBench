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
typedef  int /*<<< orphan*/  uint64_t ;
struct sysinfo {int /*<<< orphan*/  totalram; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int dwLength; int /*<<< orphan*/  ullTotalPhys; } ;
typedef  TYPE_1__ MEMORYSTATUSEX ;

/* Variables and functions */
 int CTL_HW ; 
 scalar_t__ GlobalMemoryStatusEx (TYPE_1__*) ; 
 int HW_MEMSIZE ; 
 int HW_PHYSMEM ; 
 int /*<<< orphan*/  sysctl (int*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysinfo (struct sysinfo*) ; 

__attribute__((used)) static uint64_t total_ram(void)
{
#if defined(HAVE_SYSINFO)
	struct sysinfo si;

	if (!sysinfo(&si))
		return si.totalram;
#elif defined(HAVE_BSD_SYSCTL) && (defined(HW_MEMSIZE) || defined(HW_PHYSMEM))
	int64_t physical_memory;
	int mib[2];
	size_t length;

	mib[0] = CTL_HW;
# if defined(HW_MEMSIZE)
	mib[1] = HW_MEMSIZE;
# else
	mib[1] = HW_PHYSMEM;
# endif
	length = sizeof(int64_t);
	if (!sysctl(mib, 2, &physical_memory, &length, NULL, 0))
		return physical_memory;
#elif defined(GIT_WINDOWS_NATIVE)
	MEMORYSTATUSEX memInfo;

	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	if (GlobalMemoryStatusEx(&memInfo))
		return memInfo.ullTotalPhys;
#endif
	return 0;
}