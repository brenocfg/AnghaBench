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
struct mem_region {int dummy; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_finddevice (char*) ; 
 scalar_t__ OF_getprop (scalar_t__,char*,char*,int) ; 
 scalar_t__ OF_getproplen (scalar_t__,char*) ; 
 scalar_t__ OF_hasprop (scalar_t__,char*) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int excise_fdt_reserved (struct mem_region*,int) ; 
 int excise_initrd_region (struct mem_region*,int) ; 
 int excise_msi_region (struct mem_region*,int) ; 
 scalar_t__ opal_check () ; 
 int parse_ofw_memory (scalar_t__,char*,struct mem_region*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

void
ofw_mem_regions(struct mem_region *memp, int *memsz,
		struct mem_region *availp, int *availsz)
{
	phandle_t phandle;
	int asz, msz;
	int res;
	char name[31];

	asz = msz = 0;

	/*
	 * Get memory from all the /memory nodes.
	 */
	for (phandle = OF_child(OF_peer(0)); phandle != 0;
	    phandle = OF_peer(phandle)) {
		if (OF_getprop(phandle, "name", name, sizeof(name)) <= 0)
			continue;
		if (strncmp(name, "memory", sizeof(name)) != 0 &&
		    strncmp(name, "memory@", strlen("memory@")) != 0)
			continue;

		res = parse_ofw_memory(phandle, "reg", &memp[msz]);
		msz += res;

		/*
		 * On POWER9 Systems we might have both linux,usable-memory and
		 * reg properties.  'reg' denotes all available memory, but we
		 * must use 'linux,usable-memory', a subset, as some memory
		 * regions are reserved for NVLink.
		 */
		if (OF_getproplen(phandle, "linux,usable-memory") >= 0)
			res = parse_ofw_memory(phandle, "linux,usable-memory",
			    &availp[asz]);
		else if (OF_getproplen(phandle, "available") >= 0)
			res = parse_ofw_memory(phandle, "available",
			    &availp[asz]);
		else
			res = parse_ofw_memory(phandle, "reg", &availp[asz]);
		asz += res;
	}

#ifdef FDT
	phandle = OF_finddevice("/chosen");
	if (OF_hasprop(phandle, "fdtmemreserv"))
		asz = excise_fdt_reserved(availp, asz);

	/* If the kernel is being loaded through kexec, initrd region is listed
	 * in /chosen but the region is not marked as reserved, so, we might exclude
	 * it here.
	 */
	if (OF_hasprop(phandle, "linux,initrd-start"))
		asz = excise_initrd_region(availp, asz);
#endif

#ifdef POWERNV
	if (opal_check() == 0)
		asz = excise_msi_region(availp, asz);
#endif

	*memsz = msz;
	*availsz = asz;
}