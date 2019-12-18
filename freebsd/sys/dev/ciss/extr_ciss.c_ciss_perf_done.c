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
typedef  int u_int32_t ;
struct ciss_softc {int* ciss_reply; size_t ciss_rqidx; int ciss_cycle; int ciss_max_requests; struct ciss_request* ciss_request; } ;
struct ciss_request {struct ciss_command* cr_cc; } ;
struct TYPE_2__ {int host_tag; } ;
struct ciss_command {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  cr_qhead_t ;

/* Variables and functions */
 int CISS_CYCLE_MASK ; 
 int CISS_HDR_HOST_TAG_ERROR ; 
 int /*<<< orphan*/  ciss_enqueue_complete (struct ciss_request*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,int,int) ; 
 int /*<<< orphan*/  debug (int,char*,int,char*) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
ciss_perf_done(struct ciss_softc *sc, cr_qhead_t *qh)
{
    struct ciss_request	*cr;
    struct ciss_command	*cc;
    u_int32_t		tag, index;

    debug_called(3);

    /*
     * Loop quickly taking requests from the adapter and moving them
     * to the completed queue.
     */
    for (;;) {
	tag = sc->ciss_reply[sc->ciss_rqidx];
	if ((tag & CISS_CYCLE_MASK) != sc->ciss_cycle)
	    break;
	index = tag >> 2;
	debug(2, "completed command %d%s\n", index,
	      (tag & CISS_HDR_HOST_TAG_ERROR) ? " with error" : "");
	if (index < sc->ciss_max_requests) {
	    cr = &(sc->ciss_request[index]);
	    cc = cr->cr_cc;
	    cc->header.host_tag = tag;	/* not updated by adapter */
	    ciss_enqueue_complete(cr, qh);
	} else {
	    ciss_printf(sc, "completed invalid request %d (0x%x)\n", index, tag);
	}
	if (++sc->ciss_rqidx == sc->ciss_max_requests) {
	    sc->ciss_rqidx = 0;
	    sc->ciss_cycle ^= 1;
	}
    }

}