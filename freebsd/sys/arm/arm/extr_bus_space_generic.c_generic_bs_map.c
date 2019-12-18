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
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  scalar_t__ bus_space_handle_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 void* pmap_mapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
generic_bs_map(bus_space_tag_t t, bus_addr_t bpa, bus_size_t size, int flags,
    bus_space_handle_t *bshp)
{
	void *va;

	/*
	 * We don't even examine the passed-in flags.  For ARM, the CACHEABLE
	 * flag doesn't make sense (we create VM_MEMATTR_DEVICE mappings), and
	 * the LINEAR flag is just implied because we use kva_alloc(size).
	 */
	if ((va = pmap_mapdev(bpa, size)) == NULL)
		return (ENOMEM);
	*bshp = (bus_space_handle_t)va;
	return (0);
}