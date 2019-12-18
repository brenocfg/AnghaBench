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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int u_char ;
struct adb_softc {int autopoll_mask; int /*<<< orphan*/  parent; } ;
struct adb_devinfo {int address; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_HB_SET_AUTOPOLL_MASK (int /*<<< orphan*/ ,int) ; 
 struct adb_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct adb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

u_int
adb_set_autopoll(device_t dev, u_char enable) 
{
	struct adb_devinfo *dinfo;
	struct adb_softc *sc;
	uint16_t mod = 0;

	sc = device_get_softc(device_get_parent(dev));
	dinfo = device_get_ivars(dev);
	
	mod = enable << dinfo->address;
	if (enable) {
		sc->autopoll_mask |= mod;
	} else {
		mod = ~mod;
		sc->autopoll_mask &= mod;
	}

	ADB_HB_SET_AUTOPOLL_MASK(sc->parent,sc->autopoll_mask);

	return (0);
}