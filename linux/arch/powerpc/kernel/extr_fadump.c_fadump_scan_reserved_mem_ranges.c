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
typedef  scalar_t__ u64 ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int fadump_add_mem_range (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 int /*<<< orphan*/ * of_get_property (struct device_node*,char*,int*) ; 
 scalar_t__ of_read_number (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  reserved_mrange_info ; 

__attribute__((used)) static inline int fadump_scan_reserved_mem_ranges(void)
{
	struct device_node *root;
	const __be32 *prop;
	int len, ret = -1;
	unsigned long i;

	root = of_find_node_by_path("/");
	if (!root)
		return ret;

	prop = of_get_property(root, "reserved-ranges", &len);
	if (!prop)
		return ret;

	/*
	 * Each reserved range is an (address,size) pair, 2 cells each,
	 * totalling 4 cells per range.
	 */
	for (i = 0; i < len / (sizeof(*prop) * 4); i++) {
		u64 base, size;

		base = of_read_number(prop + (i * 4) + 0, 2);
		size = of_read_number(prop + (i * 4) + 2, 2);

		if (size) {
			ret = fadump_add_mem_range(&reserved_mrange_info,
						   base, base + size);
			if (ret < 0) {
				pr_warn("some reserved ranges are ignored!\n");
				break;
			}
		}
	}

	return ret;
}