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
struct ciss_softc {scalar_t__ ciss_perf; } ;
struct ciss_request {int cr_flags; struct ciss_softc* cr_sc; } ;
typedef  int /*<<< orphan*/  cr_qhead_t ;

/* Variables and functions */
 int CISS_REQ_POLL ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ciss_complete (struct ciss_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ciss_done (struct ciss_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ciss_perf_done (struct ciss_softc*,int /*<<< orphan*/ *) ; 
 int ciss_start (struct ciss_request*) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static int
ciss_poll_request(struct ciss_request *cr, int timeout)
{
    cr_qhead_t qh;
    struct ciss_softc *sc;
    int		error;

    debug_called(2);

    STAILQ_INIT(&qh);
    sc = cr->cr_sc;
    cr->cr_flags |= CISS_REQ_POLL;
    if ((error = ciss_start(cr)) != 0)
	return(error);

    do {
	if (sc->ciss_perf)
	    ciss_perf_done(sc, &qh);
	else
	    ciss_done(sc, &qh);
	ciss_complete(sc, &qh);
	if (!(cr->cr_flags & CISS_REQ_POLL))
	    return(0);
	DELAY(1000);
    } while (timeout-- >= 0);
    return(EWOULDBLOCK);
}