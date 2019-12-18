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
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  ofw_t ;
typedef  int /*<<< orphan*/  ihandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_node_from_xref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static phandle_t
ofw_fdt_instance_to_package(ofw_t ofw, ihandle_t instance)
{

	/* Where real OF uses ihandles in the tree, FDT uses xref phandles */
	return (OF_node_from_xref(instance));
}