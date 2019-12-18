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

/* Variables and functions */
 int fdt_first_subnode (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fdt_offset_phandle (int) ; 
 int fdt_phandle_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdtp ; 

__attribute__((used)) static phandle_t
ofw_fdt_child(ofw_t ofw, phandle_t node)
{
	int offset;

	offset = fdt_phandle_offset(node);
	if (offset < 0)
		return (0);
	offset = fdt_first_subnode(fdtp, offset);
	return (fdt_offset_phandle(offset));
}