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
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ u_long ;
typedef  int phandle_t ;

/* Variables and functions */
 int OF_finddevice (char*) ; 
 int fdt_depth_search_compatible (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fdt_regsize (int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/ * ocotp_regs ; 
 scalar_t__ ocotp_size ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/ * pmap_mapdev (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
fsl_ocotp_devmap(void)
{
	phandle_t child, root;
	u_long base, size;

	if ((root = OF_finddevice("/")) == -1)
		goto fatal;
	if ((child = fdt_depth_search_compatible(root, "fsl,imx6q-ocotp", 0)) == 0)
		goto fatal;
	if (fdt_regsize(child, &base, &size) != 0)
		goto fatal;

	ocotp_size = (vm_size_t)size;

	if ((ocotp_regs = pmap_mapdev((vm_offset_t)base, ocotp_size)) == NULL)
		goto fatal;

	return;
fatal:
	panic("cannot find/map the ocotp registers");
}