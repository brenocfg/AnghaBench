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
 int __cvmx_shmem_close_dscptr (struct cvmx_shmem_dscptr*,int) ; 

__attribute__((used)) static inline int __cvmx_shmem_close_standalone(struct cvmx_shmem_dscptr *dscptr, int remove)
{
    return __cvmx_shmem_close_dscptr(dscptr, remove);
}