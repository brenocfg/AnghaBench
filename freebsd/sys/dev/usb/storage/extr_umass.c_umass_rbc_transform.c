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
struct TYPE_2__ {int cmd_len; int /*<<< orphan*/  cmd_data; } ;
struct umass_softc {int sc_quirks; TYPE_1__ sc_transfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*,int) ; 
#define  INQUIRY 140 
#define  MODE_SELECT_10 139 
#define  MODE_SENSE_10 138 
#define  PREVENT_ALLOW 137 
 int RBC_PAD_TO_12 ; 
#define  READ_10 136 
#define  READ_CAPACITY 135 
#define  REQUEST_SENSE 134 
#define  START_STOP_UNIT 133 
#define  SYNCHRONIZE_CACHE 132 
#define  TEST_UNIT_READY 131 
 int /*<<< orphan*/  UDMASS_SCSI ; 
#define  VERIFY_10 130 
#define  WRITE_10 129 
#define  WRITE_BUFFER 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
umass_rbc_transform(struct umass_softc *sc, uint8_t *cmd_ptr, uint8_t cmd_len)
{
	if ((cmd_len == 0) ||
	    (cmd_len > sizeof(sc->sc_transfer.cmd_data))) {
		DPRINTF(sc, UDMASS_SCSI, "Invalid command "
		    "length: %d bytes\n", cmd_len);
		return (0);		/* failure */
	}
	switch (cmd_ptr[0]) {
		/* these commands are defined in RBC: */
	case READ_10:
	case READ_CAPACITY:
	case START_STOP_UNIT:
	case SYNCHRONIZE_CACHE:
	case WRITE_10:
	case VERIFY_10:
	case INQUIRY:
	case MODE_SELECT_10:
	case MODE_SENSE_10:
	case TEST_UNIT_READY:
	case WRITE_BUFFER:
		/*
		 * The following commands are not listed in my copy of the
		 * RBC specs. CAM however seems to want those, and at least
		 * the Sony DSC device appears to support those as well
		 */
	case REQUEST_SENSE:
	case PREVENT_ALLOW:

		memcpy(sc->sc_transfer.cmd_data, cmd_ptr, cmd_len);

		if ((sc->sc_quirks & RBC_PAD_TO_12) && (cmd_len < 12)) {
			memset(sc->sc_transfer.cmd_data + cmd_len,
			    0, 12 - cmd_len);
			cmd_len = 12;
		}
		sc->sc_transfer.cmd_len = cmd_len;
		return (1);		/* success */

		/* All other commands are not legal in RBC */
	default:
		DPRINTF(sc, UDMASS_SCSI, "Unsupported RBC "
		    "command 0x%02x\n", cmd_ptr[0]);
		return (0);		/* failure */
	}
}