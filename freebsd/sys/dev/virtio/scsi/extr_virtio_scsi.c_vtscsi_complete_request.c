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
struct vtscsi_request {int vsr_flags; int /*<<< orphan*/  vsr_softc; int /*<<< orphan*/  (* vsr_complete ) (int /*<<< orphan*/ ,struct vtscsi_request*) ;} ;

/* Variables and functions */
 int VTSCSI_REQ_FLAG_COMPLETE ; 
 int VTSCSI_REQ_FLAG_POLLED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct vtscsi_request*) ; 

__attribute__((used)) static void
vtscsi_complete_request(struct vtscsi_request *req)
{

	if (req->vsr_flags & VTSCSI_REQ_FLAG_POLLED)
		req->vsr_flags |= VTSCSI_REQ_FLAG_COMPLETE;

	if (req->vsr_complete != NULL)
		req->vsr_complete(req->vsr_softc, req);
}