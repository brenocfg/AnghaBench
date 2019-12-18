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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct adb_softc {int /*<<< orphan*/  sc_dev; } ;
struct adb_devinfo {int register3; scalar_t__ handler_id; int /*<<< orphan*/  address; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_COMMAND_LISTEN ; 
 int /*<<< orphan*/  ADB_COMMAND_TALK ; 
 int /*<<< orphan*/  adb_send_raw_packet_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct adb_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct adb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

uint8_t 
adb_set_device_handler(device_t dev, uint8_t newhandler) 
{
	struct adb_softc *sc;
	struct adb_devinfo *dinfo;
	uint16_t newr3;

	dinfo = device_get_ivars(dev);
	sc = device_get_softc(device_get_parent(dev));

	newr3 = dinfo->register3 & 0xff00;
	newr3 |= (uint16_t)(newhandler);

	adb_send_raw_packet_sync(sc->sc_dev,dinfo->address, ADB_COMMAND_LISTEN, 
	    3, sizeof(uint16_t), (u_char *)(&newr3), NULL);
	adb_send_raw_packet_sync(sc->sc_dev,dinfo->address, 
	    ADB_COMMAND_TALK, 3, 0, NULL, NULL);

	return (dinfo->handler_id);
}