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
typedef  int /*<<< orphan*/  u_int ;
typedef  int u_char ;
struct adb_softc {int sync_packet; int /*<<< orphan*/ ** children; int /*<<< orphan*/  packet_reply; int /*<<< orphan*/ * syncreg; TYPE_1__* devinfo; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int handler_id; int /*<<< orphan*/  register3; } ;

/* Variables and functions */
 int ADB_COMMAND_TALK ; 
 int /*<<< orphan*/  ADB_RECEIVE_PACKET (int /*<<< orphan*/ *,int,int,int,int,int*) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int) ; 
 struct adb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  wakeup (struct adb_softc*) ; 

u_int
adb_receive_raw_packet(device_t dev, u_char status, u_char command, int len, 
    u_char *data) 
{
	struct adb_softc *sc = device_get_softc(dev);
	u_char addr = command >> 4;

	if (len > 0 && (command & 0x0f) == ((ADB_COMMAND_TALK << 2) | 3)) {
		memcpy(&sc->devinfo[addr].register3,data,2);
		sc->devinfo[addr].handler_id = data[1];
	}

	if (sc->sync_packet == command)  {
		memcpy(sc->syncreg,data,(len > 8) ? 8 : len);
		atomic_store_rel_int(&sc->packet_reply,len + 1);
		wakeup(sc);
	}

	if (sc->children[addr] != NULL) {
		ADB_RECEIVE_PACKET(sc->children[addr],status,
			(command & 0x0f) >> 2,command & 0x03,len,data);
	}
	
	return (0);
}