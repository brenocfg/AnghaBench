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
struct scsi_start_stop_unit {int how; } ;
struct cfumass_softc {int /*<<< orphan*/  sc_current_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFUMASS_DEBUG (struct cfumass_softc*,char*,...) ; 
 int /*<<< orphan*/  CFUMASS_T_STATUS ; 
 int /*<<< orphan*/  CFUMASS_WARN (struct cfumass_softc*,char*) ; 
 int SSS_LOEJ ; 
 int SSS_PC_MASK ; 
 int SSS_START ; 
#define  START_STOP_UNIT 128 
 int /*<<< orphan*/  cfumass_transfer_start (struct cfumass_softc*,int /*<<< orphan*/ ) ; 
 int ignore_stop ; 

__attribute__((used)) static int
cfumass_quirk(struct cfumass_softc *sc, unsigned char *cdb, int cdb_len)
{
	struct scsi_start_stop_unit *sssu;

	switch (cdb[0]) {
	case START_STOP_UNIT:
		/*
		 * Some initiators - eg OSX, Darwin Kernel Version 15.6.0,
		 * root:xnu-3248.60.11~2/RELEASE_X86_64 - attempt to stop
		 * the unit on eject, but fail to start it when it's plugged
		 * back.  Just ignore the command.
		 */

		if (cdb_len < sizeof(*sssu)) {
			CFUMASS_DEBUG(sc, "received START STOP UNIT with "
			    "bCDBLength %d, should be %zd",
			    cdb_len, sizeof(*sssu));
			break;
		}

		sssu = (struct scsi_start_stop_unit *)cdb;
		if ((sssu->how & SSS_PC_MASK) != 0)
			break;

		if ((sssu->how & SSS_START) != 0)
			break;

		if ((sssu->how & SSS_LOEJ) != 0)
			break;
		
		if (ignore_stop == 0) {
			break;
		} else if (ignore_stop == 1) {
			CFUMASS_WARN(sc, "ignoring START STOP UNIT request");
		} else {
			CFUMASS_DEBUG(sc, "ignoring START STOP UNIT request");
		}

		sc->sc_current_status = 0;
		cfumass_transfer_start(sc, CFUMASS_T_STATUS);

		return (1);
	default:
		break;
	}

	return (0);
}