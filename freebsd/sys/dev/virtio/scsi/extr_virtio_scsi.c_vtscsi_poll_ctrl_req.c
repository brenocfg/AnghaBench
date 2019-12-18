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
struct vtscsi_softc {int /*<<< orphan*/  vtscsi_control_vq; } ;
struct vtscsi_request {int vsr_flags; } ;

/* Variables and functions */
 int VTSCSI_REQ_FLAG_COMPLETE ; 
 int VTSCSI_REQ_FLAG_POLLED ; 
 int /*<<< orphan*/  vtscsi_complete_vq (struct vtscsi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtscsi_poll_ctrl_req(struct vtscsi_softc *sc, struct vtscsi_request *req)
{

	/* XXX We probably shouldn't poll forever. */
	req->vsr_flags |= VTSCSI_REQ_FLAG_POLLED;
	do
		vtscsi_complete_vq(sc, sc->vtscsi_control_vq);
	while ((req->vsr_flags & VTSCSI_REQ_FLAG_COMPLETE) == 0);

	req->vsr_flags &= ~VTSCSI_REQ_FLAG_POLLED;
}