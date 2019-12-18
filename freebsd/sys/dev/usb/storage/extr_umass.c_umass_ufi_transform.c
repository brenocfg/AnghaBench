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
struct TYPE_2__ {int* cmd_data; int /*<<< orphan*/  cmd_len; } ;
struct umass_softc {int sc_quirks; TYPE_1__ sc_transfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*,...) ; 
#define  FORMAT_UNIT 147 
#define  INQUIRY 146 
#define  MODE_SELECT_10 145 
#define  MODE_SENSE_10 144 
 int NO_TEST_UNIT_READY ; 
#define  POSITION_TO_ELEMENT 143 
#define  PREVENT_ALLOW 142 
#define  READ_10 141 
#define  READ_12 140 
#define  READ_CAPACITY 139 
#define  READ_FORMAT_CAPACITIES 138 
#define  REQUEST_SENSE 137 
#define  REZERO_UNIT 136 
#define  SEND_DIAGNOSTIC 135 
 int SSS_START ; 
#define  START_STOP_UNIT 134 
#define  SYNCHRONIZE_CACHE 133 
#define  TEST_UNIT_READY 132 
 int /*<<< orphan*/  UDMASS_SCSI ; 
 int /*<<< orphan*/  UDMASS_UFI ; 
 int /*<<< orphan*/  UFI_COMMAND_LENGTH ; 
#define  VERIFY 131 
#define  WRITE_10 130 
#define  WRITE_12 129 
#define  WRITE_AND_VERIFY 128 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
umass_ufi_transform(struct umass_softc *sc, uint8_t *cmd_ptr,
    uint8_t cmd_len)
{
	if ((cmd_len == 0) ||
	    (cmd_len > sizeof(sc->sc_transfer.cmd_data))) {
		DPRINTF(sc, UDMASS_SCSI, "Invalid command "
		    "length: %d bytes\n", cmd_len);
		return (0);		/* failure */
	}
	/* An UFI command is always 12 bytes in length */
	sc->sc_transfer.cmd_len = UFI_COMMAND_LENGTH;

	/* Zero the command data */
	memset(sc->sc_transfer.cmd_data, 0, UFI_COMMAND_LENGTH);

	switch (cmd_ptr[0]) {
		/*
		 * Commands of which the format has been verified. They
		 * should work. Copy the command into the (zeroed out)
		 * destination buffer.
		 */
	case TEST_UNIT_READY:
		if (sc->sc_quirks & NO_TEST_UNIT_READY) {
			/*
			 * Some devices do not support this command. Start
			 * Stop Unit should give the same results
			 */
			DPRINTF(sc, UDMASS_UFI, "Converted TEST_UNIT_READY "
			    "to START_UNIT\n");

			sc->sc_transfer.cmd_data[0] = START_STOP_UNIT;
			sc->sc_transfer.cmd_data[4] = SSS_START;
			return (1);
		}
		break;

	case REZERO_UNIT:
	case REQUEST_SENSE:
	case FORMAT_UNIT:
	case INQUIRY:
	case START_STOP_UNIT:
	case SEND_DIAGNOSTIC:
	case PREVENT_ALLOW:
	case READ_CAPACITY:
	case READ_10:
	case WRITE_10:
	case POSITION_TO_ELEMENT:	/* SEEK_10 */
	case WRITE_AND_VERIFY:
	case VERIFY:
	case MODE_SELECT_10:
	case MODE_SENSE_10:
	case READ_12:
	case WRITE_12:
	case READ_FORMAT_CAPACITIES:
		break;

		/*
		 * SYNCHRONIZE_CACHE isn't supported by UFI, nor should it be
		 * required for UFI devices, so it is appropriate to fake
		 * success.
		 */
	case SYNCHRONIZE_CACHE:
		return (2);

	default:
		DPRINTF(sc, UDMASS_SCSI, "Unsupported UFI "
		    "command 0x%02x\n", cmd_ptr[0]);
		return (0);		/* failure */
	}

	memcpy(sc->sc_transfer.cmd_data, cmd_ptr, cmd_len);
	return (1);			/* success */
}