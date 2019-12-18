#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_int32_t ;
struct resource {int dummy; } ;
struct bios_smap {scalar_t__ type; scalar_t__ length; scalar_t__ base; } ;
typedef  scalar_t__ rman_res_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * caddr_t ;
struct TYPE_2__ {scalar_t__ rm_end; } ;

/* Variables and functions */
 char* ELF_KERN_STR ; 
 int MODINFOMD_SMAP ; 
 int MODINFO_METADATA ; 
 scalar_t__ SMAP_TYPE_MEMORY ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 scalar_t__* dump_avail ; 
 TYPE_1__ mem_rman ; 
 int /*<<< orphan*/  panic (char*,int,...) ; 
 int /*<<< orphan*/ * preload_search_by_type (char*) ; 
 scalar_t__ preload_search_info (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ram_attach(device_t dev)
{
	struct bios_smap *smapbase, *smap, *smapend;
	struct resource *res;
	rman_res_t length;
	vm_paddr_t *p;
	caddr_t kmdp;
	uint32_t smapsize;
	int error, rid;

	/* Retrieve the system memory map from the loader. */
	kmdp = preload_search_by_type("elf kernel");
	if (kmdp == NULL)
		kmdp = preload_search_by_type(ELF_KERN_STR);  
	smapbase = (struct bios_smap *)preload_search_info(kmdp,
	    MODINFO_METADATA | MODINFOMD_SMAP);
	if (smapbase != NULL) {
		smapsize = *((u_int32_t *)smapbase - 1);
		smapend = (struct bios_smap *)((uintptr_t)smapbase + smapsize);

		rid = 0;
		for (smap = smapbase; smap < smapend; smap++) {
			if (smap->type != SMAP_TYPE_MEMORY ||
			    smap->length == 0)
				continue;
			if (smap->base > mem_rman.rm_end)
				continue;
			length = smap->base + smap->length > mem_rman.rm_end ?
			    mem_rman.rm_end - smap->base : smap->length;
			error = bus_set_resource(dev, SYS_RES_MEMORY, rid,
			    smap->base, length);
			if (error)
				panic(
				    "ram_attach: resource %d failed set with %d",
				    rid, error);
			res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid,
			    0);
			if (res == NULL)
				panic("ram_attach: resource %d failed to attach",
				    rid);
			rid++;
		}
		return (0);
	}

	/*
	 * If the system map is not available, fall back to using
	 * dump_avail[].  We use the dump_avail[] array rather than
	 * phys_avail[] for the memory map as phys_avail[] contains
	 * holes for kernel memory, page 0, the message buffer, and
	 * the dcons buffer.  We test the end address in the loop
	 * instead of the start since the start address for the first
	 * segment is 0.
	 */
	for (rid = 0, p = dump_avail; p[1] != 0; rid++, p += 2) {
		if (p[0] > mem_rman.rm_end)
			break;
		length = (p[1] > mem_rman.rm_end ? mem_rman.rm_end : p[1]) -
		    p[0];
		error = bus_set_resource(dev, SYS_RES_MEMORY, rid, p[0],
		    length);
		if (error)
			panic("ram_attach: resource %d failed set with %d", rid,
			    error);
		res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &rid, 0);
		if (res == NULL)
			panic("ram_attach: resource %d failed to attach", rid);
	}
	return (0);
}