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
struct TYPE_2__ {int /*<<< orphan*/  dequeue_no_requests; } ;
struct vtscsi_softc {TYPE_1__ vtscsi_stats; int /*<<< orphan*/  vtscsi_req_free; } ;
struct vtscsi_request {int /*<<< orphan*/  vsr_state; } ;

/* Variables and functions */
 struct vtscsi_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct vtscsi_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTSCSI_REQ_STATE_INUSE ; 
 int /*<<< orphan*/  VTSCSI_TRACE ; 
 int /*<<< orphan*/  vsr_link ; 
 int /*<<< orphan*/  vtscsi_dprintf (struct vtscsi_softc*,int /*<<< orphan*/ ,char*,struct vtscsi_request*) ; 

__attribute__((used)) static struct vtscsi_request *
vtscsi_dequeue_request(struct vtscsi_softc *sc)
{
	struct vtscsi_request *req;

	req = TAILQ_FIRST(&sc->vtscsi_req_free);
	if (req != NULL) {
		req->vsr_state = VTSCSI_REQ_STATE_INUSE;
		TAILQ_REMOVE(&sc->vtscsi_req_free, req, vsr_link);
	} else
		sc->vtscsi_stats.dequeue_no_requests++;

	vtscsi_dprintf(sc, VTSCSI_TRACE, "req=%p\n", req);

	return (req);
}