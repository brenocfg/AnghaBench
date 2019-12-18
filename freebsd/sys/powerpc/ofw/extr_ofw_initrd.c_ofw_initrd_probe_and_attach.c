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
typedef  int vm_paddr_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int ssize_t ;
typedef  scalar_t__ phandle_t ;
typedef  int pcell_t ;
typedef  int /*<<< orphan*/  cell ;

/* Variables and functions */
 scalar_t__ OF_finddevice (char*) ; 
 int OF_getencprop (scalar_t__,char*,int*,int) ; 
 int /*<<< orphan*/  OF_hasprop (scalar_t__,char*) ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  hw_direct_map ; 
 int /*<<< orphan*/ * mfs_root ; 
 int mfs_root_size ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ofw_initrd_probe_and_attach(void *junk)
{
	phandle_t chosen;
	vm_paddr_t start, end;
	pcell_t cell[2];
	ssize_t size;

	if (!hw_direct_map)
		return;

	chosen = OF_finddevice("/chosen");
	if (chosen <= 0)
		return;

	if (!OF_hasprop(chosen, "linux,initrd-start") ||
	    !OF_hasprop(chosen, "linux,initrd-end"))
		return;

	size = OF_getencprop(chosen, "linux,initrd-start", cell, sizeof(cell));
	if (size == 4)
		start = cell[0];
	else if (size == 8)
		start = (uint64_t)cell[0] << 32 | cell[1];
	else {
		printf("ofw_initrd: Wrong linux,initrd-start size\n");
		return;
	}

	size = OF_getencprop(chosen, "linux,initrd-end", cell, sizeof(cell));
	if (size == 4)
		end = cell[0];
	else if (size == 8)
		end = (uint64_t)cell[0] << 32 | cell[1];
	else{
		printf("ofw_initrd: Wrong linux,initrd-end size\n");
		return;
	}

	if (end - start > 0) {
		mfs_root = (u_char *) PHYS_TO_DMAP(start);
		mfs_root_size = end - start;
		printf("ofw_initrd: initrd loaded at 0x%08lx-0x%08lx\n",
			start, end);
	}
}