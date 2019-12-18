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
struct TYPE_2__ {int cmd_len; int /*<<< orphan*/ * cmd_data; } ;
struct umass_softc {int sc_quirks; TYPE_1__ sc_transfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int FORCE_SHORT_INQUIRY ; 
#define  INQUIRY 129 
 int NO_TEST_UNIT_READY ; 
 int /*<<< orphan*/  SHORT_INQUIRY_LENGTH ; 
 int /*<<< orphan*/  SSS_START ; 
 int /*<<< orphan*/  START_STOP_UNIT ; 
#define  TEST_UNIT_READY 128 
 int /*<<< orphan*/  UDMASS_SCSI ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
umass_scsi_transform(struct umass_softc *sc, uint8_t *cmd_ptr,
    uint8_t cmd_len)
{
	if ((cmd_len == 0) ||
	    (cmd_len > sizeof(sc->sc_transfer.cmd_data))) {
		DPRINTF(sc, UDMASS_SCSI, "Invalid command "
		    "length: %d bytes\n", cmd_len);
		return (0);		/* failure */
	}
	sc->sc_transfer.cmd_len = cmd_len;

	switch (cmd_ptr[0]) {
	case TEST_UNIT_READY:
		if (sc->sc_quirks & NO_TEST_UNIT_READY) {
			DPRINTF(sc, UDMASS_SCSI, "Converted TEST_UNIT_READY "
			    "to START_UNIT\n");
			memset(sc->sc_transfer.cmd_data, 0, cmd_len);
			sc->sc_transfer.cmd_data[0] = START_STOP_UNIT;
			sc->sc_transfer.cmd_data[4] = SSS_START;
			return (1);
		}
		break;

	case INQUIRY:
		/*
		 * some drives wedge when asked for full inquiry
		 * information.
		 */
		if (sc->sc_quirks & FORCE_SHORT_INQUIRY) {
			memcpy(sc->sc_transfer.cmd_data, cmd_ptr, cmd_len);
			sc->sc_transfer.cmd_data[4] = SHORT_INQUIRY_LENGTH;
			return (1);
		}
		break;
	}

	memcpy(sc->sc_transfer.cmd_data, cmd_ptr, cmd_len);
	return (1);
}