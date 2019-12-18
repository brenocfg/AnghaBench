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
struct cvmx_shmem_smdr {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {size_t size; int /*<<< orphan*/  base_addr; } ;
typedef  TYPE_1__ cvmx_bootmem_named_block_desc_t ;

/* Variables and functions */
 char* CVMX_SHMEM_DSCPTR_NAME ; 
 struct cvmx_shmem_smdr* __smdr ; 
 int /*<<< orphan*/  __smdr_new (struct cvmx_shmem_smdr*) ; 
 scalar_t__ cvmx_bootmem_alloc_named (size_t,int,char*) ; 
 TYPE_1__* cvmx_bootmem_find_named_block (char*) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 scalar_t__ cvmx_phys_to_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct cvmx_shmem_smdr *__smdr_init()
{
    const cvmx_bootmem_named_block_desc_t *smdr_nblk = NULL;
    size_t smdr_size = sizeof(*__smdr);
    char *smdr_name = CVMX_SHMEM_DSCPTR_NAME;

    __smdr = (struct cvmx_shmem_smdr *) cvmx_bootmem_alloc_named(smdr_size, 0x10000, smdr_name);

    if (__smdr)
       __smdr_new (__smdr);
    else
    {
        /* Check if SMDR exists already */
        smdr_nblk = cvmx_bootmem_find_named_block(smdr_name);
        if (smdr_nblk)
        {
            __smdr = (struct cvmx_shmem_smdr *)
            (cvmx_phys_to_ptr(smdr_nblk->base_addr));

            cvmx_spinlock_lock (&__smdr->lock);
            if (smdr_nblk->size != smdr_size)
            {
                cvmx_dprintf("SMDR named block is created by another "
                    "application with different size %lu, "
                    "expecting %lu \n",
                    (long unsigned int)smdr_nblk->size, (long unsigned int)smdr_size);
                __smdr = NULL;
            }
            cvmx_spinlock_unlock (&__smdr->lock);
        }
    }

   if (!__smdr)
       cvmx_dprintf("cvmx_shmem: Failed to allocate or find SMDR from bootmem \n");

   return __smdr;
}