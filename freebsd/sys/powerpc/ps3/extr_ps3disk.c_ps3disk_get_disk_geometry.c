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
typedef  int uint64_t ;
struct ps3disk_softc {int /*<<< orphan*/  sc_nblocks; int /*<<< orphan*/  sc_blksize; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PS3_LPAR_ID_PME ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int lv1_get_repository_node_value (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int lv1_repository_string (char*) ; 
 int ps3bus_get_busidx (int /*<<< orphan*/ ) ; 
 int ps3bus_get_devidx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ps3disk_get_disk_geometry(struct ps3disk_softc *sc)
{
	device_t dev = sc->sc_dev;
	uint64_t bus_index = ps3bus_get_busidx(dev);
	uint64_t dev_index = ps3bus_get_devidx(dev);
	uint64_t junk;
	int err;

	err = lv1_get_repository_node_value(PS3_LPAR_ID_PME,
	    (lv1_repository_string("bus") >> 32) | bus_index,
	    lv1_repository_string("dev") | dev_index,
	    lv1_repository_string("blk_size"), 0, &sc->sc_blksize, &junk);
	if (err) {
		device_printf(dev, "Could not get block size (0x%08x)\n", err);
		return (ENXIO);
	}

	err = lv1_get_repository_node_value(PS3_LPAR_ID_PME,
	    (lv1_repository_string("bus") >> 32) | bus_index,
	    lv1_repository_string("dev") | dev_index,
	    lv1_repository_string("n_blocks"), 0, &sc->sc_nblocks, &junk);
	if (err) {
		device_printf(dev, "Could not get total number of blocks "
		    "(0x%08x)\n", err);
		err = ENXIO;
	}

	return (err);
}