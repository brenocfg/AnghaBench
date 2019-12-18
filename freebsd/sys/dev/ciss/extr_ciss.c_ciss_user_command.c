#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ciss_softc {int /*<<< orphan*/  ciss_mtx; } ;
struct ciss_request {int /*<<< orphan*/ * cr_data; int /*<<< orphan*/  cr_length; struct ciss_command* cr_cc; } ;
struct ciss_error_info {int dummy; } ;
struct TYPE_4__ {int host_tag; int /*<<< orphan*/  address; } ;
struct ciss_command {TYPE_1__ header; int /*<<< orphan*/ * sg; int /*<<< orphan*/  cdb; } ;
struct TYPE_5__ {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf; int /*<<< orphan*/  error_info; struct ciss_error_info Request; struct ciss_error_info LUN_info; } ;
typedef  TYPE_2__ IOCTL_Command_struct ;

/* Variables and functions */
 int CISS_HDR_HOST_TAG_ERROR ; 
 int /*<<< orphan*/  CISS_MALLOC_CLASS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PPAUSE ; 
 int /*<<< orphan*/  bcopy (struct ciss_error_info*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bzero (struct ciss_error_info*,int) ; 
 scalar_t__ ciss_get_request (struct ciss_softc*,struct ciss_request**) ; 
 int /*<<< orphan*/  ciss_release_request (struct ciss_request*) ; 
 int ciss_synch_request (struct ciss_request*,int) ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct ciss_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ciss_user_command(struct ciss_softc *sc, IOCTL_Command_struct *ioc)
{
    struct ciss_request		*cr;
    struct ciss_command		*cc;
    struct ciss_error_info	*ce;
    int				error = 0;

    debug_called(1);

    cr = NULL;

    /*
     * Get a request.
     */
    while (ciss_get_request(sc, &cr) != 0)
	msleep(sc, &sc->ciss_mtx, PPAUSE, "cissREQ", hz);
    cc = cr->cr_cc;

    /*
     * Allocate an in-kernel databuffer if required, copy in user data.
     */
    mtx_unlock(&sc->ciss_mtx);
    cr->cr_length = ioc->buf_size;
    if (ioc->buf_size > 0) {
	if ((cr->cr_data = malloc(ioc->buf_size, CISS_MALLOC_CLASS, M_NOWAIT)) == NULL) {
	    error = ENOMEM;
	    goto out_unlocked;
	}
	if ((error = copyin(ioc->buf, cr->cr_data, ioc->buf_size))) {
	    debug(0, "copyin: bad data buffer %p/%d", ioc->buf, ioc->buf_size);
	    goto out_unlocked;
	}
    }

    /*
     * Build the request based on the user command.
     */
    bcopy(&ioc->LUN_info, &cc->header.address, sizeof(cc->header.address));
    bcopy(&ioc->Request, &cc->cdb, sizeof(cc->cdb));

    /* XXX anything else to populate here? */
    mtx_lock(&sc->ciss_mtx);

    /*
     * Run the command.
     */
    if ((error = ciss_synch_request(cr, 60 * 1000))) {
	debug(0, "request failed - %d", error);
	goto out;
    }

    /*
     * Check to see if the command succeeded.
     */
    ce = (struct ciss_error_info *)&(cc->sg[0]);
    if ((cc->header.host_tag & CISS_HDR_HOST_TAG_ERROR) == 0)
	bzero(ce, sizeof(*ce));

    /*
     * Copy the results back to the user.
     */
    bcopy(ce, &ioc->error_info, sizeof(*ce));
    mtx_unlock(&sc->ciss_mtx);
    if ((ioc->buf_size > 0) &&
	(error = copyout(cr->cr_data, ioc->buf, ioc->buf_size))) {
	debug(0, "copyout: bad data buffer %p/%d", ioc->buf, ioc->buf_size);
	goto out_unlocked;
    }

    /* done OK */
    error = 0;

out_unlocked:
    mtx_lock(&sc->ciss_mtx);

out:
    if ((cr != NULL) && (cr->cr_data != NULL))
	free(cr->cr_data, CISS_MALLOC_CLASS);
    if (cr != NULL)
	ciss_release_request(cr);
    return(error);
}