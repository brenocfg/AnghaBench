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
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct device_node* of_find_node_by_path (char*) ; 
 int of_n_addr_cells (struct device_node*) ; 
 int of_n_size_cells (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int get_addr_size_cells(int *addr_cells, int *size_cells)
{
	struct device_node *root;

	root = of_find_node_by_path("/");
	if (!root)
		return -EINVAL;

	*addr_cells = of_n_addr_cells(root);
	*size_cells = of_n_size_cells(root);

	of_node_put(root);

	return 0;
}