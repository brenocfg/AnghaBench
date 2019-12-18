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
typedef  unsigned long uint64_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int fdt_del_mem_rsv (void*,int) ; 
 int fdt_get_mem_rsv (void*,int,unsigned long*,unsigned long*) ; 
 int fdt_num_mem_rsv (void*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int delete_fdt_mem_rsv(void *fdt, unsigned long start, unsigned long size)
{
	int i, ret, num_rsvs = fdt_num_mem_rsv(fdt);

	for (i = 0; i < num_rsvs; i++) {
		uint64_t rsv_start, rsv_size;

		ret = fdt_get_mem_rsv(fdt, i, &rsv_start, &rsv_size);
		if (ret) {
			pr_err("Malformed device tree.\n");
			return -EINVAL;
		}

		if (rsv_start == start && rsv_size == size) {
			ret = fdt_del_mem_rsv(fdt, i);
			if (ret) {
				pr_err("Error deleting device tree reservation.\n");
				return -EINVAL;
			}

			return 0;
		}
	}

	return -ENOENT;
}