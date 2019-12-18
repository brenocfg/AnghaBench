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
typedef  int /*<<< orphan*/  u_int ;
typedef  int u_char ;
struct adb_softc {int /*<<< orphan*/  parent; } ;
struct adb_devinfo {int address; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_HB_SEND_RAW_PACKET (int /*<<< orphan*/ ,int,int,int*,int) ; 
 struct adb_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct adb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

u_int 
adb_send_packet(device_t dev, u_char command, u_char reg, int len, u_char *data)
{
	u_char command_byte = 0;
	struct adb_devinfo *dinfo;
	struct adb_softc *sc;

	sc = device_get_softc(device_get_parent(dev));
	dinfo = device_get_ivars(dev);
	
	command_byte |= dinfo->address << 4;
	command_byte |= command << 2;
	command_byte |= reg;

	ADB_HB_SEND_RAW_PACKET(sc->parent, command_byte, len, data, 1);

	return (0);
}