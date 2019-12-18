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
typedef  int /*<<< orphan*/  uint64_t ;
struct octeon_device {int dummy; } ;
struct cvmx_bootmem_named_block_desc {int /*<<< orphan*/  size; int /*<<< orphan*/  base_addr; } ;

/* Variables and functions */
 struct cvmx_bootmem_named_block_desc* __cvmx_bootmem_find_named_block_flags (struct octeon_device*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_remote_lock () ; 
 int /*<<< orphan*/  lio_remote_unlock () ; 

__attribute__((used)) static int
lio_named_block_find(struct octeon_device *oct, const char *name,
		     uint64_t * base_addr, uint64_t * size)
{
	const struct cvmx_bootmem_named_block_desc	*named_block;

	lio_remote_lock();
	named_block = __cvmx_bootmem_find_named_block_flags(oct, name, 0);
	lio_remote_unlock();
	if (named_block != NULL) {
		*base_addr = named_block->base_addr;
		*size = named_block->size;
		return (0);
	}

	return (1);
}