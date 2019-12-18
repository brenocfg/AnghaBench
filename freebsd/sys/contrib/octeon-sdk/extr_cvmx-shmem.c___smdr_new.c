#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cvmx_shmem_smdr {int /*<<< orphan*/  lock; void* break64; TYPE_1__* shmd; } ;
struct TYPE_2__ {scalar_t__ alignment; scalar_t__ size; scalar_t__ paddr; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/ * name; scalar_t__ use_count; scalar_t__ is_named_block; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int CVMX_SHMEM_NUM_DSCPTR ; 
 int /*<<< orphan*/  CVMX_SHMEM_OWNER_NONE ; 
 scalar_t__ CVMX_SHMEM_VADDR64_START ; 
 int /*<<< orphan*/  __CHECK_APP_SMDR ; 
 int /*<<< orphan*/  cvmx_spinlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void __smdr_new(struct cvmx_shmem_smdr *smdr) {

    if (smdr != NULL)
    {
        int i;

        cvmx_spinlock_init (&smdr->lock);
        cvmx_spinlock_lock (&smdr->lock);

        for ( i = 0; i < CVMX_SHMEM_NUM_DSCPTR; i++ )
        {
            smdr -> shmd[i].owner = CVMX_SHMEM_OWNER_NONE;
            smdr -> shmd[i].is_named_block = 0;
            smdr -> shmd[i].use_count = 0;
            smdr -> shmd[i].name = NULL;
            smdr -> shmd[i].vaddr = NULL;
            smdr -> shmd[i].paddr = 0;
            smdr -> shmd[i].size = 0;
            smdr -> shmd[i].alignment = 0;
        };

        /* Init vaddr */
        smdr->break64 = (void *)CVMX_SHMEM_VADDR64_START;
        cvmx_spinlock_unlock (&smdr->lock);
    }

    /* Make sure the shmem descriptor region is created */
    __CHECK_APP_SMDR;
}