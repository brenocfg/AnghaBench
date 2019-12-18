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
struct ciss_softc {int ciss_flags; } ;
struct ciss_request {int dummy; } ;

/* Variables and functions */
#define  CISS_CMD_STATUS_SUCCESS 128 
 int /*<<< orphan*/  CISS_COMMAND_ABORT_NOTIFY ; 
 int CISS_FLAG_NOTIFY_OK ; 
 int EIO ; 
 int ciss_get_bmic_request (struct ciss_softc*,struct ciss_request**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ciss_name_command_status (int) ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,int) ; 
 int /*<<< orphan*/  ciss_release_request (struct ciss_request*) ; 
 int /*<<< orphan*/  ciss_report_request (struct ciss_request*,int*,int /*<<< orphan*/ *) ; 
 int ciss_synch_request (struct ciss_request*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
ciss_notify_abort_bmic(struct ciss_softc *sc)
{
    struct ciss_request			*cr;
    int					error, command_status;

    debug_called(1);

    cr = NULL;
    error = 0;

    /* verify that there's an outstanding command */
    if (!(sc->ciss_flags & CISS_FLAG_NOTIFY_OK))
	goto out;

    /*
     * Build a BMIC command to cancel the Notify on Event command.
     *
     * Note that we are sending a CISS opcode here.  Odd.
     */
    if ((error = ciss_get_bmic_request(sc, &cr, CISS_COMMAND_ABORT_NOTIFY,
				       NULL, 0)) != 0)
	goto out;

    /*
     * Submit the request and wait for it to complete.
     */
    if ((error = ciss_synch_request(cr, 60 * 1000)) != 0) {
	ciss_printf(sc, "error sending BMIC Cancel Notify on Event command (%d)\n", error);
	goto out;
    }

    /*
     * Check response.
     */
    ciss_report_request(cr, &command_status, NULL);
    switch(command_status) {
    case CISS_CMD_STATUS_SUCCESS:
	break;
    default:
	ciss_printf(sc, "error cancelling Notify on Event (%s)\n",
		    ciss_name_command_status(command_status));
	error = EIO;
	goto out;
    }

out:
    if (cr != NULL)
	ciss_release_request(cr);
    return(error);
}