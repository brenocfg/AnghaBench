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
struct cvmx_bootmem_named_block_desc {int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct cvmx_bootmem_named_block_desc* cvmx_bootmem_find_named_block (char const*) ; 
 void* cvmx_phys_to_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void *cvmx_get_memory_addr(const char* buf_name)
{
    void *buffer_ptr = NULL;
    const struct cvmx_bootmem_named_block_desc *block_desc = cvmx_bootmem_find_named_block(buf_name);
    if (block_desc)
        buffer_ptr = cvmx_phys_to_ptr(block_desc->base_addr);
    assert (buffer_ptr != NULL);

    return buffer_ptr;
}