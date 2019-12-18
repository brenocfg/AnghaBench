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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {char const* name; void* base; scalar_t__ starting_element_count; scalar_t__ size; } ;

/* Variables and functions */
 int CVMX_FPA_ALIGNMENT ; 
 scalar_t__ CVMX_FPA_MIN_BLOCK_SIZE ; 
 scalar_t__ CVMX_FPA_NUM_POOLS ; 
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 
 int /*<<< orphan*/  cvmx_fpa_free (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* cvmx_fpa_pool_info ; 

int cvmx_fpa_setup_pool(uint64_t pool, const char *name, void *buffer,
                         uint64_t block_size, uint64_t num_blocks)
{
    char *ptr;
    if (!buffer)
    {
        cvmx_dprintf("ERROR: cvmx_fpa_setup_pool: NULL buffer pointer!\n");
        return -1;
    }
    if (pool >= CVMX_FPA_NUM_POOLS)
    {
        cvmx_dprintf("ERROR: cvmx_fpa_setup_pool: Illegal pool!\n");
        return -1;
    }

    if (block_size < CVMX_FPA_MIN_BLOCK_SIZE)
    {
        cvmx_dprintf("ERROR: cvmx_fpa_setup_pool: Block size too small.\n");
        return -1;
    }

    if (((unsigned long)buffer & (CVMX_FPA_ALIGNMENT-1)) != 0)
    {
        cvmx_dprintf("ERROR: cvmx_fpa_setup_pool: Buffer not aligned properly.\n");
        return -1;
    }

    cvmx_fpa_pool_info[pool].name = name;
    cvmx_fpa_pool_info[pool].size = block_size;
    cvmx_fpa_pool_info[pool].starting_element_count = num_blocks;
    cvmx_fpa_pool_info[pool].base = buffer;

    ptr = (char*)buffer;
    while (num_blocks--)
    {
        cvmx_fpa_free(ptr, pool, 0);
        ptr += block_size;
    }
    return 0;
}