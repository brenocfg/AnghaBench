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
 int /*<<< orphan*/  ATAPI_COMMAND_LENGTH ; 
 int /*<<< orphan*/  DPRINTF (struct umass_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int FORCE_SHORT_INQUIRY ; 
#define  INQUIRY 144 
#define  MODE_SELECT_10 143 
#define  MODE_SENSE_10 142 
 int NO_TEST_UNIT_READY ; 
#define  POSITION_TO_ELEMENT 141 
#define  PREVENT_ALLOW 140 
#define  READ_10 139 
#define  READ_12 138 
#define  READ_BUFFER 137 
#define  READ_CAPACITY 136 
#define  REQUEST_SENSE 135 
#define  REZERO_UNIT 134 
#define  SEND_DIAGNOSTIC 133 
 int SHORT_INQUIRY_LENGTH ; 
 int SSS_START ; 
#define  START_STOP_UNIT 132 
#define  SYNCHRONIZE_CACHE 131 
#define  TEST_UNIT_READY 130 
 int /*<<< orphan*/  UDMASS_SCSI ; 
#define  WRITE_10 129 
#define  WRITE_12 128 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t
umass_atapi_transform(struct umass_softc *sc, uint8_t *cmd_ptr,
    uint8_t cmd_len)
{
	if ((cmd_len == 0) ||
	    (cmd_len > sizeof(sc->sc_transfer.cmd_data))) {
		DPRINTF(sc, UDMASS_SCSI, "Invalid command "
		    "length: %d bytes\n", cmd_len);
		return (0);		/* failure */
	}
	/* An ATAPI command is always 12 bytes in length. */
	sc->sc_transfer.cmd_len = ATAPI_COMMAND_LENGTH;

	/* Zero the command data */
	memset(sc->sc_transfer.cmd_data, 0, ATAPI_COMMAND_LENGTH);

	switch (cmd_ptr[0]) {
		/*
		 * Commands of which the format has been verified. They
		 * should work. Copy the command into the destination
		 * buffer.
		 */
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

	case TEST_UNIT_READY:
		if (sc->sc_quirks & NO_TEST_UNIT_READY) {
			DPRINTF(sc, UDMASS_SCSI, "Converted TEST_UNIT_READY "
			    "to START_UNIT\n");
			sc->sc_transfer.cmd_data[0] = START_STOP_UNIT;
			sc->sc_transfer.cmd_data[4] = SSS_START;
			return (1);
		}
		break;

	case REZERO_UNIT:
	case REQUEST_SENSE:
	case START_STOP_UNIT:
	case SEND_DIAGNOSTIC:
	case PREVENT_ALLOW:
	case READ_CAPACITY:
	case READ_10:
	case WRITE_10:
	case POSITION_TO_ELEMENT:	/* SEEK_10 */
	case SYNCHRONIZE_CACHE:
	case MODE_SELECT_10:
	case MODE_SENSE_10:
	case READ_BUFFER:
	case 0x42:			/* READ_SUBCHANNEL */
	case 0x43:			/* READ_TOC */
	case 0x44:			/* READ_HEADER */
	case 0x47:			/* PLAY_MSF (Play Minute/Second/Frame) */
	case 0x48:			/* PLAY_TRACK */
	case 0x49:			/* PLAY_TRACK_REL */
	case 0x4b:			/* PAUSE */
	case 0x51:			/* READ_DISK_INFO */
	case 0x52:			/* READ_TRACK_INFO */
	case 0x54:			/* SEND_OPC */
	case 0x59:			/* READ_MASTER_CUE */
	case 0x5b:			/* CLOSE_TR_SESSION */
	case 0x5c:			/* READ_BUFFER_CAP */
	case 0x5d:			/* SEND_CUE_SHEET */
	case 0xa1:			/* BLANK */
	case 0xa5:			/* PLAY_12 */
	case 0xa6:			/* EXCHANGE_MEDIUM */
	case 0xad:			/* READ_DVD_STRUCTURE */
	case 0xbb:			/* SET_CD_SPEED */
	case 0xe5:			/* READ_TRACK_INFO_PHILIPS */
		break;

	case READ_12:
	case WRITE_12:
	default:
		DPRINTF(sc, UDMASS_SCSI, "Unsupported ATAPI "
		    "command 0x%02x - trying anyway\n",
		    cmd_ptr[0]);
		break;
	}

	memcpy(sc->sc_transfer.cmd_data, cmd_ptr, cmd_len);
	return (1);			/* success */
}