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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_char ;
struct adb_softc {int sync_packet; int /*<<< orphan*/  enum_hook; TYPE_1__* devinfo; int /*<<< orphan*/ * children; scalar_t__ autopoll_mask; scalar_t__ packet_reply; int /*<<< orphan*/  parent; int /*<<< orphan*/  sc_dev; } ;
typedef  scalar_t__ next_free ;
typedef  int int8_t ;
typedef  scalar_t__ i ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int address; int default_address; int register3; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_COMMAND_BUS_RESET ; 
 int /*<<< orphan*/  ADB_COMMAND_LISTEN ; 
 int /*<<< orphan*/  ADB_COMMAND_TALK ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int adb_send_raw_packet_sync (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct adb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
adb_bus_enumerate(void *xdev)
{
	device_t dev = (device_t)xdev;

	struct adb_softc *sc = device_get_softc(dev);
	uint8_t i, next_free;
	uint16_t r3;

	sc->sc_dev = dev;
	sc->parent = device_get_parent(dev);

	sc->packet_reply = 0;
	sc->autopoll_mask = 0;
	sc->sync_packet = 0xffff;

	/* Initialize devinfo */
	for (i = 0; i < 16; i++) {
		sc->devinfo[i].address = i;
		sc->devinfo[i].default_address = 0;
	}
	
	/* Reset ADB bus */
	adb_send_raw_packet_sync(dev,0,ADB_COMMAND_BUS_RESET,0,0,NULL,NULL);
	DELAY(1500);

	/* Enumerate bus */
	next_free = 8;

	for (i = 1; i <= 7; i++) {
	    int8_t first_relocated = -1;
	    int reply = 0;

	    do {
		reply = adb_send_raw_packet_sync(dev,i,
			    ADB_COMMAND_TALK,3,0,NULL,NULL);
	
		if (reply) {
			/* If we got a response, relocate to next_free */
			r3 = sc->devinfo[i].register3;
			r3 &= 0xf000;
			r3 |= ((uint16_t)(next_free) & 0x000f) << 8;
			r3 |= 0x00fe;

			adb_send_raw_packet_sync(dev,i, ADB_COMMAND_LISTEN,3,
			    sizeof(uint16_t),(u_char *)(&r3),NULL);

			adb_send_raw_packet_sync(dev,next_free,
			    ADB_COMMAND_TALK,3,0,NULL,NULL);

			sc->devinfo[next_free].default_address = i;
			if (first_relocated < 0)
				first_relocated = next_free;

			next_free++;
		} else if (first_relocated > 0) {
			/* Collisions removed, relocate first device back */

			r3 = sc->devinfo[i].register3;
			r3 &= 0xf000;
			r3 |= ((uint16_t)(i) & 0x000f) << 8;
			
			adb_send_raw_packet_sync(dev,first_relocated,
			    ADB_COMMAND_LISTEN,3,
			    sizeof(uint16_t),(u_char *)(&r3),NULL);
			adb_send_raw_packet_sync(dev,i,
			    ADB_COMMAND_TALK,3,0,NULL,NULL);

			sc->devinfo[i].default_address = i;
			sc->devinfo[(int)(first_relocated)].default_address = 0;
			break;
		}
	    } while (reply);
	}

	for (i = 0; i < 16; i++) {
		if (sc->devinfo[i].default_address) {
			sc->children[i] = device_add_child(dev, NULL, -1);
			device_set_ivars(sc->children[i], &sc->devinfo[i]);
		}
	}

	bus_generic_attach(dev);

	config_intrhook_disestablish(&sc->enum_hook);
}