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
 int __cvmx_shmem_close_linux (struct cvmx_shmem_dscptr*,int) ; 
 int __cvmx_shmem_close_standalone (struct cvmx_shmem_dscptr*,int) ; 

int cvmx_shmem_close(struct cvmx_shmem_dscptr *dscptr, int remove)
{
    int ret;
#ifdef CVMX_BUILD_FOR_LINUX_USER
    ret = __cvmx_shmem_close_linux(dscptr, remove);
#else
    ret = __cvmx_shmem_close_standalone(dscptr, remove);
#endif
    return ret;
}