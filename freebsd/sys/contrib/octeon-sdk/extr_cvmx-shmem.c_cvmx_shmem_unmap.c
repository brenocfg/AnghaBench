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
 int /*<<< orphan*/  __cvmx_shmem_unmap_linux (struct cvmx_shmem_dscptr*) ; 
 int /*<<< orphan*/  __cvmx_shmem_unmap_standalone (struct cvmx_shmem_dscptr*) ; 

void cvmx_shmem_unmap(struct cvmx_shmem_dscptr *dscptr)
{
#ifdef CVMX_BUILD_FOR_LINUX_USER
    __cvmx_shmem_unmap_linux(dscptr);
#else
    __cvmx_shmem_unmap_standalone(dscptr);
#endif
}