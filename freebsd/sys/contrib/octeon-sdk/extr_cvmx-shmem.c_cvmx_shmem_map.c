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
struct cvmx_shmem_dscptr {int dummy; } ;

/* Variables and functions */
 void* __cvmx_shmem_map_linux (struct cvmx_shmem_dscptr*,int) ; 
 void* __cvmx_shmem_map_standalone (struct cvmx_shmem_dscptr*,int) ; 

void *cvmx_shmem_map(struct cvmx_shmem_dscptr *dscptr, int pflag)
{
    void *vaddr = NULL;
#ifdef CVMX_BUILD_FOR_LINUX_USER
    vaddr = __cvmx_shmem_map_linux(dscptr, pflag);
#else
    vaddr = __cvmx_shmem_map_standalone(dscptr, pflag);
#endif
    return vaddr;
}