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
struct cvmx_shmem_dscptr {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SHMEM_OWNER_NONE ; 

__attribute__((used)) static void __cvmx_shmem_smdr_free(struct cvmx_shmem_dscptr *dscptr)
{
    dscptr->owner = CVMX_SHMEM_OWNER_NONE;
}