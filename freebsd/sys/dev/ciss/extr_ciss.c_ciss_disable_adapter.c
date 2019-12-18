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
struct ciss_softc {int ciss_max_requests; struct ciss_request* ciss_request; int /*<<< orphan*/  ciss_flags; int /*<<< orphan*/  ciss_dev; } ;
struct ciss_request {int cr_flags; int /*<<< orphan*/  (* cr_complete ) (struct ciss_request*) ;struct ciss_command* cr_cc; } ;
struct ciss_error_info {int /*<<< orphan*/  command_status; } ;
struct ciss_command {int /*<<< orphan*/ * sg; } ;
typedef  int /*<<< orphan*/  cr_qhead_t ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_CMD_STATUS_HARDWARE_ERROR ; 
 int /*<<< orphan*/  CISS_FLAG_RUNNING ; 
 int CISS_REQ_BUSY ; 
 int CISS_REQ_SLEEP ; 
 int /*<<< orphan*/  CISS_TL_SIMPLE_DISABLE_INTERRUPTS (struct ciss_softc*) ; 
 struct ciss_request* ciss_dequeue_complete (struct ciss_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ciss_enqueue_complete (struct ciss_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ciss_request*) ; 
 int /*<<< orphan*/  wakeup (struct ciss_request*) ; 

__attribute__((used)) static void
ciss_disable_adapter(struct ciss_softc *sc)
{
    cr_qhead_t			qh;
    struct ciss_request		*cr;
    struct ciss_command		*cc;
    struct ciss_error_info	*ce;
    int				i;

    CISS_TL_SIMPLE_DISABLE_INTERRUPTS(sc);
    pci_disable_busmaster(sc->ciss_dev);
    sc->ciss_flags &= ~CISS_FLAG_RUNNING;

    for (i = 1; i < sc->ciss_max_requests; i++) {
	cr = &sc->ciss_request[i];
	if ((cr->cr_flags & CISS_REQ_BUSY) == 0)
	    continue;

	cc = cr->cr_cc;
	ce = (struct ciss_error_info *)&(cc->sg[0]);
	ce->command_status = CISS_CMD_STATUS_HARDWARE_ERROR;
	ciss_enqueue_complete(cr, &qh);
    }

    for (;;) {
	if ((cr = ciss_dequeue_complete(sc, &qh)) == NULL)
	    break;
    
	/*
	 * If the request has a callback, invoke it.
	 */
	if (cr->cr_complete != NULL) {
	    cr->cr_complete(cr);
	    continue;
	}

	/*
	 * If someone is sleeping on this request, wake them up.
	 */
	if (cr->cr_flags & CISS_REQ_SLEEP) {
	    cr->cr_flags &= ~CISS_REQ_SLEEP;
	    wakeup(cr);
	    continue;
	}
    }
}