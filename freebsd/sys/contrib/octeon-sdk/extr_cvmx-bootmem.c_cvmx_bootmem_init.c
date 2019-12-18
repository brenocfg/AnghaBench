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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  cvmx_spinlock_t ;

/* Variables and functions */
 scalar_t__ cvmx_bootmem_desc_addr ; 
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 

int cvmx_bootmem_init(uint64_t mem_desc_addr)
{
    /* Verify that the size of cvmx_spinlock_t meets our assumptions */
    if (sizeof(cvmx_spinlock_t) != 4)
    {
        cvmx_dprintf("ERROR: Unexpected size of cvmx_spinlock_t\n");
        return(-1);
    }
    if (!cvmx_bootmem_desc_addr)
        cvmx_bootmem_desc_addr = mem_desc_addr;
    return(0);
}