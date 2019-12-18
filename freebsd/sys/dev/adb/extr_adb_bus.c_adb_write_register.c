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
typedef  int /*<<< orphan*/  u_char ;
struct adb_softc {int /*<<< orphan*/  sc_dev; } ;
struct adb_devinfo {int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_COMMAND_LISTEN ; 
 int /*<<< orphan*/  ADB_COMMAND_TALK ; 
 size_t adb_send_raw_packet_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct adb_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct adb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

size_t 
adb_write_register(device_t dev, u_char reg, size_t len, void *data) 
{
	struct adb_softc *sc;
	struct adb_devinfo *dinfo;
	size_t result;
	
	dinfo = device_get_ivars(dev);
	sc = device_get_softc(device_get_parent(dev));
	
	result = adb_send_raw_packet_sync(sc->sc_dev,dinfo->address,
		   ADB_COMMAND_LISTEN, reg, len, (u_char *)data, NULL);
	
	result = adb_send_raw_packet_sync(sc->sc_dev,dinfo->address,
	           ADB_COMMAND_TALK, reg, 0, NULL, NULL);

	return (result);
}