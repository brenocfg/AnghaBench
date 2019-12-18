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
typedef  int uint8_t ;
typedef  int u_char ;
struct adb_softc {int sync_packet; int packet_reply; int /*<<< orphan*/  syncreg; int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADB_HB_SEND_RAW_PACKET (int /*<<< orphan*/ ,int,int,int*,int) ; 
 int /*<<< orphan*/  atomic_cmpset_int (int*,int,int) ; 
 int /*<<< orphan*/  atomic_fetchadd_int (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set_int (int*,int) ; 
 struct adb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tsleep (struct adb_softc*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int 
adb_send_raw_packet_sync(device_t dev, uint8_t to, uint8_t command, 
    uint8_t reg, int len, u_char *data, u_char *reply) 
{
	u_char command_byte = 0;
	struct adb_softc *sc;
	int result = -1;
	int i = 1;

	sc = device_get_softc(dev);
	
	command_byte |= to << 4;
	command_byte |= command << 2;
	command_byte |= reg;

	/* Wait if someone else has a synchronous request pending */
	while (!atomic_cmpset_int(&sc->sync_packet, 0xffff, command_byte))
		tsleep(sc, 0, "ADB sync", hz/10);

	sc->packet_reply = 0;
	sc->sync_packet = command_byte;

	ADB_HB_SEND_RAW_PACKET(sc->parent, command_byte, len, data, 1);

	while (!atomic_fetchadd_int(&sc->packet_reply,0)) {
		/*
		 * Maybe the command got lost? Try resending and polling the 
		 * controller.
		 */
		if (i % 40 == 0)
			ADB_HB_SEND_RAW_PACKET(sc->parent, command_byte, 
			    len, data, 1);

		tsleep(sc, 0, "ADB sync", hz/10);
		i++;
	}

	result = sc->packet_reply - 1;

	if (reply != NULL && result > 0)
		memcpy(reply,sc->syncreg,result);

	/* Clear packet sync */
	sc->packet_reply = 0;

	/*
	 * We can't match a value beyond 8 bits, so set sync_packet to 
	 * 0xffff to avoid collisions.
	 */
	atomic_set_int(&sc->sync_packet, 0xffff); 

	return (result);
}