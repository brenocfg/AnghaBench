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

size_t h2o_numproc(void)
{
#if defined(_SC_NPROCESSORS_ONLN)
    return (size_t)sysconf(_SC_NPROCESSORS_ONLN);
#elif defined(CTL_HW) && defined(HW_AVAILCPU)
    int name[] = {CTL_HW, HW_AVAILCPU};
    int ncpu;
    size_t ncpu_sz = sizeof(ncpu);
    if (sysctl(name, sizeof(name) / sizeof(name[0]), &ncpu, &ncpu_sz, NULL, 0) != 0 || sizeof(ncpu) != ncpu_sz) {
        h2o_error_printf("[ERROR] failed to obtain number of CPU cores, assuming as one\n");
        ncpu = 1;
    }
    return ncpu;
#else
    return 1;
#endif
}