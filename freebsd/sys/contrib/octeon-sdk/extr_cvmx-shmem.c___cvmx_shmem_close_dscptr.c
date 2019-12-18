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
struct cvmx_shmem_dscptr {scalar_t__ use_count; int /*<<< orphan*/  lock; int /*<<< orphan*/  name; scalar_t__ is_named_block; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cvmx_shmem_smdr_free (struct cvmx_shmem_dscptr*) ; 
 int /*<<< orphan*/  cvmx_bootmem_phy_named_block_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int __cvmx_shmem_close_dscptr(struct cvmx_shmem_dscptr *dscptr, int remove)
{
    cvmx_spinlock_lock(&dscptr->lock);

    if (dscptr->use_count >0)
        dscptr->use_count-= 1;

    if ((dscptr->use_count == 0) && remove)
    {
        /* Free this descriptor */
        __cvmx_shmem_smdr_free(dscptr);

        /* Free named block if this is the last user, and the block
           is created by the application */
        if (dscptr->is_named_block)
        {
#ifdef DEBUG
            cvmx_dprintf("cvmx-shmem-dbg: remove named block %s \n", dscptr->name);
#endif
            cvmx_bootmem_phy_named_block_free(dscptr->name, 0);
        }
    }
    cvmx_spinlock_unlock(&dscptr->lock);
    return 0;
}