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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 
 int tpm_tis12_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tpm_isa_probe(device_t dev)
{
	bus_space_tag_t iot;
	bus_space_handle_t ioh;
	struct resource *mem_res;
	int rv, mem_rid;

	mem_rid = 0;
	mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &mem_rid,
	    RF_ACTIVE);
	if (mem_res == NULL)
		return (ENXIO);
	iot = rman_get_bustag(mem_res);
	ioh = rman_get_bushandle(mem_res);

	if ((rv = tpm_tis12_probe(iot, ioh)))
		device_set_desc(dev, "Trusted Platform Module");

	bus_release_resource(dev, SYS_RES_MEMORY, mem_rid, mem_res);
	return rv ? 0 : ENXIO;
}