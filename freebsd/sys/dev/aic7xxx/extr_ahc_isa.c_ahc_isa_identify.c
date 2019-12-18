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
typedef  int uint32_t ;
struct resource {int dummy; } ;
struct aic7770_identity {int dummy; } ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_EISA_IOSIZE ; 
 int AHC_EISA_SLOT_OFFSET ; 
 int AHC_EISA_SLOT_SIZE ; 
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ISA_ORDER_SPECULATIVE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 struct aic7770_identity* ahc_isa_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 struct resource* bus_alloc_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_driver (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 

__attribute__((used)) static void
ahc_isa_identify(driver_t *driver, device_t parent)
{
	int slot;
	int max_slot;

	max_slot = 14;
	for (slot = 0; slot <= max_slot; slot++) {
		struct aic7770_identity *entry;
		bus_space_tag_t	    tag;
		bus_space_handle_t  bsh;
		struct resource	   *regs;
		uint32_t	    iobase;
		int		    rid;

		rid = 0;
		iobase = (slot * AHC_EISA_SLOT_SIZE) + AHC_EISA_SLOT_OFFSET;
		regs = bus_alloc_resource(parent, SYS_RES_IOPORT, &rid,
					  iobase, iobase, AHC_EISA_IOSIZE,
					  RF_ACTIVE);
		if (regs == NULL) {
			if (bootverbose)
				printf("ahc_isa_identify %d: ioport 0x%x "
				       "alloc failed\n", slot, iobase);
			continue;
		}

		tag = rman_get_bustag(regs);
		bsh = rman_get_bushandle(regs);

		entry = ahc_isa_find_device(tag, bsh);
		if (entry != NULL) {
			device_t child;

			child = BUS_ADD_CHILD(parent, ISA_ORDER_SPECULATIVE,
					      "ahc", -1);
			if (child != NULL) {
				device_set_driver(child, driver);
				bus_set_resource(child, SYS_RES_IOPORT,
						 0, iobase, AHC_EISA_IOSIZE);
			}
		}
		bus_release_resource(parent, SYS_RES_IOPORT, rid, regs);
	}
}