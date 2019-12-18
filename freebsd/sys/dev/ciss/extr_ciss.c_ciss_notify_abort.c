#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ciss_softc {int ciss_flags; int /*<<< orphan*/  ciss_mtx; struct ciss_request* ciss_periodic_notify; } ;
struct ciss_request {int /*<<< orphan*/ * cr_data; struct ciss_command* cr_cc; int /*<<< orphan*/  cr_length; } ;
struct ciss_notify_cdb {int /*<<< orphan*/  length; int /*<<< orphan*/  command; int /*<<< orphan*/  opcode; } ;
struct TYPE_8__ {int cdb_length; int /*<<< orphan*/ * cdb; scalar_t__ timeout; int /*<<< orphan*/  direction; int /*<<< orphan*/  attribute; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {scalar_t__ target; scalar_t__ bus; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {TYPE_1__ physical; } ;
struct TYPE_7__ {TYPE_2__ address; } ;
struct ciss_command {TYPE_4__ cdb; TYPE_3__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_CDB_ATTRIBUTE_SIMPLE ; 
 int /*<<< orphan*/  CISS_CDB_DIRECTION_READ ; 
 int /*<<< orphan*/  CISS_CDB_TYPE_COMMAND ; 
#define  CISS_CMD_STATUS_INVALID_COMMAND 130 
#define  CISS_CMD_STATUS_SUCCESS 129 
#define  CISS_CMD_STATUS_TARGET_STATUS 128 
 int /*<<< orphan*/  CISS_COMMAND_ABORT_NOTIFY ; 
 int CISS_FLAG_NOTIFY_OK ; 
 int /*<<< orphan*/  CISS_HDR_ADDRESS_MODE_PERIPHERAL ; 
 int /*<<< orphan*/  CISS_MALLOC_CLASS ; 
 int /*<<< orphan*/  CISS_NOTIFY_DATA_SIZE ; 
 int /*<<< orphan*/  CISS_OPCODE_WRITE ; 
 int CISS_SCSI_STATUS_CHECK_CONDITION ; 
 int EIO ; 
 int ENOMEM ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  bzero (struct ciss_notify_cdb*,int) ; 
 int ciss_get_request (struct ciss_softc*,struct ciss_request**) ; 
 int /*<<< orphan*/  ciss_name_command_status (int) ; 
 int ciss_notify_abort_bmic (struct ciss_softc*) ; 
 int /*<<< orphan*/  ciss_print_request (struct ciss_request*) ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,...) ; 
 int /*<<< orphan*/  ciss_release_request (struct ciss_request*) ; 
 int /*<<< orphan*/  ciss_report_request (struct ciss_request*,int*,int*) ; 
 int ciss_synch_request (struct ciss_request*,int) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int msleep (struct ciss_request**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
ciss_notify_abort(struct ciss_softc *sc)
{
    struct ciss_request		*cr;
    struct ciss_command		*cc;
    struct ciss_notify_cdb	*cnc;
    int				error, command_status, scsi_status;

    debug_called(1);

    cr = NULL;
    error = 0;

    /* verify that there's an outstanding command */
    if (!(sc->ciss_flags & CISS_FLAG_NOTIFY_OK))
	goto out;

    /* get a command to issue the abort with */
    if ((error = ciss_get_request(sc, &cr)))
	goto out;

    /* get a buffer for the result */
    if ((cr->cr_data = malloc(CISS_NOTIFY_DATA_SIZE, CISS_MALLOC_CLASS, M_NOWAIT)) == NULL) {
	debug(0, "can't get notify event request buffer");
	error = ENOMEM;
	goto out;
    }
    cr->cr_length = CISS_NOTIFY_DATA_SIZE;

    /* build the CDB */
    cc = cr->cr_cc;
    cc->header.address.physical.mode = CISS_HDR_ADDRESS_MODE_PERIPHERAL;
    cc->header.address.physical.bus = 0;
    cc->header.address.physical.target = 0;
    cc->cdb.cdb_length = sizeof(*cnc);
    cc->cdb.type = CISS_CDB_TYPE_COMMAND;
    cc->cdb.attribute = CISS_CDB_ATTRIBUTE_SIMPLE;
    cc->cdb.direction = CISS_CDB_DIRECTION_READ;
    cc->cdb.timeout = 0;	/* no timeout, we hope */

    cnc = (struct ciss_notify_cdb *)&(cc->cdb.cdb[0]);
    bzero(cnc, sizeof(*cnc));
    cnc->opcode = CISS_OPCODE_WRITE;
    cnc->command = CISS_COMMAND_ABORT_NOTIFY;
    cnc->length = htonl(CISS_NOTIFY_DATA_SIZE);
#if 0
    ciss_print_request(cr);
#endif

    /*
     * Submit the request and wait for it to complete.
     */
    if ((error = ciss_synch_request(cr, 60 * 1000)) != 0) {
	ciss_printf(sc, "Abort Notify Event command failed (%d)\n", error);
	goto out;
    }

    /*
     * Check response.
     */
    ciss_report_request(cr, &command_status, &scsi_status);
    switch(command_status) {
    case CISS_CMD_STATUS_SUCCESS:
	break;
    case CISS_CMD_STATUS_INVALID_COMMAND:
	/*
	 * Some older adapters don't support the CISS version of this
	 * command.  Fall back to using the BMIC version.
	 */
	error = ciss_notify_abort_bmic(sc);
	if (error != 0)
	    goto out;
	break;

    case CISS_CMD_STATUS_TARGET_STATUS:
	/*
	 * This can happen if the adapter thinks there wasn't an outstanding
	 * Notify Event command but we did.  We clean up here.
	 */
	if (scsi_status == CISS_SCSI_STATUS_CHECK_CONDITION) {
	    if (sc->ciss_periodic_notify != NULL)
		ciss_release_request(sc->ciss_periodic_notify);
	    error = 0;
	    goto out;
	}
	/* FALLTHROUGH */

    default:
	ciss_printf(sc, "Abort Notify Event command failed (%s)\n",
		    ciss_name_command_status(command_status));
	error = EIO;
	goto out;
    }

    /*
     * Sleep waiting for the notifier command to complete.  Note
     * that if it doesn't, we may end up in a bad situation, since
     * the adapter may deliver it later.  Also note that the adapter
     * requires the Notify Event command to be cancelled in order to
     * maintain internal bookkeeping.
     */
    while (sc->ciss_periodic_notify != NULL) {
	error = msleep(&sc->ciss_periodic_notify, &sc->ciss_mtx, PRIBIO, "cissNEA", hz * 5);
	if (error == EWOULDBLOCK) {
	    ciss_printf(sc, "Notify Event command failed to abort, adapter may wedge.\n");
	    break;
	}
    }

 out:
    /* release the cancel request */
    if (cr != NULL) {
	if (cr->cr_data != NULL)
	    free(cr->cr_data, CISS_MALLOC_CLASS);
	ciss_release_request(cr);
    }
    if (error == 0)
	sc->ciss_flags &= ~CISS_FLAG_NOTIFY_OK;
    return(error);
}