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
typedef  size_t uint64_t ;
struct TYPE_2__ {int starting_element_count; void* base; int size; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_dprintf (char*,unsigned long long,int,unsigned long long,...) ; 
 void* cvmx_fpa_alloc (size_t) ; 
 TYPE_1__* cvmx_fpa_pool_info ; 
 size_t cvmx_ptr_to_phys (void*) ; 

uint64_t cvmx_fpa_shutdown_pool(uint64_t pool)
{
    int errors = 0;
    int count  = 0;
    int expected_count = cvmx_fpa_pool_info[pool].starting_element_count;
    uint64_t base   = cvmx_ptr_to_phys(cvmx_fpa_pool_info[pool].base);
    uint64_t finish = base + cvmx_fpa_pool_info[pool].size * expected_count;

    count = 0;
    while (1)
    {
        uint64_t address;
        void *ptr = cvmx_fpa_alloc(pool);
        if (!ptr)
            break;

        address = cvmx_ptr_to_phys(ptr);
        if ((address >= base) && (address < finish) &&
            (((address - base) % cvmx_fpa_pool_info[pool].size) == 0))
        {
            count++;
        }
        else
        {
            cvmx_dprintf("ERROR: cvmx_fpa_shutdown_pool: Illegal address 0x%llx in pool %s(%d)\n",
                   (unsigned long long)address, cvmx_fpa_pool_info[pool].name, (int)pool);
            errors++;
        }
    }

    if (count < expected_count)
    {
        cvmx_dprintf("ERROR: cvmx_fpa_shutdown_pool: Pool %s(%d) missing %d buffers\n",
               cvmx_fpa_pool_info[pool].name, (int)pool, expected_count - count);
    }
    else if (count > expected_count)
    {
        cvmx_dprintf("ERROR: cvmx_fpa_shutdown_pool: Pool %s(%d) had %d duplicate buffers\n",
               cvmx_fpa_pool_info[pool].name, (int)pool, count - expected_count);
    }

    if (errors)
    {
        cvmx_dprintf("ERROR: cvmx_fpa_shutdown_pool: Pool %s(%d) started at 0x%llx, ended at 0x%llx, with a step of 0x%x\n",
               cvmx_fpa_pool_info[pool].name, (int)pool, (unsigned long long)base, (unsigned long long)finish, (int)cvmx_fpa_pool_info[pool].size);
        return -errors;
    }
    else
        return expected_count - count;
}