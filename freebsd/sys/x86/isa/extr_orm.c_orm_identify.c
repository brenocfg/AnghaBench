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
typedef  int u_int8_t ;
typedef  scalar_t__ u_int32_t ;
struct resource {int dummy; } ;
struct orm_softc {int rnum; int* rid; struct resource** res; } ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ IOMEM_END ; 
 scalar_t__ IOMEM_START ; 
 scalar_t__ IOMEM_STEP ; 
 int /*<<< orphan*/  ISA_ORDER_SENSITIVE ; 
 int MAX_ROMS ; 
 int /*<<< orphan*/  ORM_ID ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_space_read_region_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct orm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isa_set_logicalid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_set_vendorid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_disabled (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 

__attribute__((used)) static void
orm_identify(driver_t* driver, device_t parent)
{
	bus_space_handle_t	bh;
	bus_space_tag_t		bt;
	device_t		child;
	u_int32_t		chunk = IOMEM_START;
	struct resource		*res;
	int			rid;
	u_int32_t		rom_size;
	struct orm_softc	*sc;
	u_int8_t		buf[3];

	if (resource_disabled("orm", 0))
		return;

	child = BUS_ADD_CHILD(parent, ISA_ORDER_SENSITIVE, "orm", -1);
	device_set_driver(child, driver);
	isa_set_logicalid(child, ORM_ID);
	isa_set_vendorid(child, ORM_ID);
	sc = device_get_softc(child);
	sc->rnum = 0;
	while (sc->rnum < MAX_ROMS && chunk < IOMEM_END) {
		bus_set_resource(child, SYS_RES_MEMORY, sc->rnum, chunk,
		    IOMEM_STEP);
		rid = sc->rnum;
		res = bus_alloc_resource_any(child, SYS_RES_MEMORY, &rid,
		    RF_ACTIVE);
		if (res == NULL) {
			bus_delete_resource(child, SYS_RES_MEMORY, sc->rnum);
			chunk += IOMEM_STEP;
			continue;
		}
		bt = rman_get_bustag(res);
		bh = rman_get_bushandle(res);
		bus_space_read_region_1(bt, bh, 0, buf, sizeof(buf));

		/*
		 * We need to release and delete the resource since we're
		 * changing its size, or the rom isn't there.  There
		 * is a checksum field in the ROM to prevent false
		 * positives.  However, some common hardware (IBM thinkpads)
		 * neglects to put a valid checksum in the ROM, so we do
		 * not double check the checksum here.  On the ISA bus
		 * areas that have no hardware read back as 0xff, so the
		 * tests to see if we have 0x55 followed by 0xaa are
		 * generally sufficient.
		 */
		bus_release_resource(child, SYS_RES_MEMORY, rid, res);
		bus_delete_resource(child, SYS_RES_MEMORY, sc->rnum);
		if (buf[0] != 0x55 || buf[1] != 0xAA || (buf[2] & 0x03) != 0) {
			chunk += IOMEM_STEP;
			continue;
		}
		rom_size = buf[2] << 9;
		bus_set_resource(child, SYS_RES_MEMORY, sc->rnum, chunk,
		    rom_size);
		rid = sc->rnum;
		res = bus_alloc_resource_any(child, SYS_RES_MEMORY, &rid, 0);
		if (res == NULL) {
			bus_delete_resource(child, SYS_RES_MEMORY, sc->rnum);
			chunk += IOMEM_STEP;
			continue;
		}
		sc->rid[sc->rnum] = rid;
		sc->res[sc->rnum] = res;
		sc->rnum++;
		chunk += rom_size;
	}

	if (sc->rnum == 0)
		device_delete_child(parent, child);
	else if (sc->rnum == 1)
		device_set_desc(child, "ISA Option ROM");
	else
		device_set_desc(child, "ISA Option ROMs");
}