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

/* Variables and functions */
 int ENOENT ; 
 int get_addr_size_cells (int*,int*) ; 
 void* of_read_number (void const*,int) ; 

__attribute__((used)) static int do_get_kexec_buffer(const void *prop, int len, unsigned long *addr,
			       size_t *size)
{
	int ret, addr_cells, size_cells;

	ret = get_addr_size_cells(&addr_cells, &size_cells);
	if (ret)
		return ret;

	if (len < 4 * (addr_cells + size_cells))
		return -ENOENT;

	*addr = of_read_number(prop, addr_cells);
	*size = of_read_number(prop + 4 * addr_cells, size_cells);

	return 0;
}