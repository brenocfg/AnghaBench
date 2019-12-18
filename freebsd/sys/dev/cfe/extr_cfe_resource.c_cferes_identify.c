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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
struct resource {int dummy; } ;
struct cferes_softc {int rnum; int* rid; struct resource** res; } ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  CFE_FLG_FULL_ARENA ; 
 scalar_t__ CFE_MI_RESERVED ; 
 size_t MAX_CFE_RESERVATIONS ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ bootverbose ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int cfe_enummem (int,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cferes_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 char* device_getnameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_driver (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cferes_identify(driver_t* driver, device_t parent)
{
	device_t		 child;
	int			 i;
	struct resource		*res;
	int			 result;
	int			 rid;
	struct cferes_softc	*sc;
	uint64_t		 addr, len, type;

	child = BUS_ADD_CHILD(parent, 100, "cferes", -1);
	device_set_driver(child, driver);
	sc = device_get_softc(child);

	sc->rnum = 0;
	for (i = 0; i < ~0U; i++) {
		result = cfe_enummem(i, CFE_FLG_FULL_ARENA, &addr, &len, &type);
		if (result < 0)
			break;
		if (type != CFE_MI_RESERVED) {
			if (bootverbose)
			printf("%s: skipping non reserved range 0x%0jx(%jd)\n",
			    device_getnameunit(child),
			    (uintmax_t)addr, (uintmax_t)len);
			continue;
		}

		bus_set_resource(child, SYS_RES_MEMORY, sc->rnum, addr, len);
		rid = sc->rnum;
		res = bus_alloc_resource_any(child, SYS_RES_MEMORY, &rid, 0);
		if (res == NULL) {
			bus_delete_resource(child, SYS_RES_MEMORY, sc->rnum);
			continue;
		}
		sc->rid[sc->rnum] = rid;
		sc->res[sc->rnum] = res;

		sc->rnum++;
		if (sc->rnum == MAX_CFE_RESERVATIONS)
			break;
	}

	if (sc->rnum == 0) {
		device_delete_child(parent, child);
		return;
	}

	device_set_desc(child, "CFE reserved memory");
}