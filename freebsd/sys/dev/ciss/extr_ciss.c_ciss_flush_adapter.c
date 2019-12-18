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
struct ciss_softc {int dummy; } ;
struct ciss_request {int dummy; } ;
struct ciss_bmic_flush_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_BMIC_FLUSH_CACHE ; 
#define  CISS_CMD_STATUS_SUCCESS 128 
 int /*<<< orphan*/  CISS_MALLOC_CLASS ; 
 int EIO ; 
 int ENOMEM ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int ciss_get_bmic_request (struct ciss_softc*,struct ciss_request**,int /*<<< orphan*/ ,void**,int) ; 
 int ciss_name_command_status (int) ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,int) ; 
 int /*<<< orphan*/  ciss_release_request (struct ciss_request*) ; 
 int /*<<< orphan*/  ciss_report_request (struct ciss_request*,int*,int /*<<< orphan*/ *) ; 
 int ciss_synch_request (struct ciss_request*,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (struct ciss_bmic_flush_cache*,int /*<<< orphan*/ ) ; 
 struct ciss_bmic_flush_cache* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ciss_flush_adapter(struct ciss_softc *sc)
{
    struct ciss_request			*cr;
    struct ciss_bmic_flush_cache	*cbfc;
    int					error, command_status;

    debug_called(1);

    cr = NULL;
    cbfc = NULL;

    /*
     * Build a BMIC request to flush the cache.  We don't disable
     * it, as we may be going to do more I/O (eg. we are emulating
     * the Synchronise Cache command).
     */
    if ((cbfc = malloc(sizeof(*cbfc), CISS_MALLOC_CLASS, M_NOWAIT | M_ZERO)) == NULL) {
	error = ENOMEM;
	goto out;
    }
    if ((error = ciss_get_bmic_request(sc, &cr, CISS_BMIC_FLUSH_CACHE,
				       (void **)&cbfc, sizeof(*cbfc))) != 0)
	goto out;

    /*
     * Submit the request and wait for it to complete.
     */
    if ((error = ciss_synch_request(cr, 60 * 1000)) != 0) {
	ciss_printf(sc, "error sending BMIC FLUSH_CACHE command (%d)\n", error);
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
	ciss_printf(sc, "error flushing cache (%s)\n",
		    ciss_name_command_status(command_status));
	error = EIO;
	goto out;
    }

out:
    if (cbfc != NULL)
	free(cbfc, CISS_MALLOC_CLASS);
    if (cr != NULL)
	ciss_release_request(cr);
    return(error);
}