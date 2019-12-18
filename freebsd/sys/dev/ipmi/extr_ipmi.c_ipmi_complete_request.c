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
struct ipmi_softc {int dummy; } ;
struct ipmi_request {struct ipmi_device* ir_owner; } ;
struct ipmi_device {struct ipmi_request ipmi_requests; scalar_t__ ipmi_closing; int /*<<< orphan*/  ipmi_select; int /*<<< orphan*/  ipmi_completed_requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_LOCK_ASSERT (struct ipmi_softc*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ipmi_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ir_link ; 
 int /*<<< orphan*/  selwakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct ipmi_request*) ; 

void
ipmi_complete_request(struct ipmi_softc *sc, struct ipmi_request *req)
{
	struct ipmi_device *dev;

	IPMI_LOCK_ASSERT(sc);

	/*
	 * Anonymous requests (from inside the driver) always have a
	 * waiter that we awaken.
	 */
	if (req->ir_owner == NULL)
		wakeup(req);
	else {
		dev = req->ir_owner;
		TAILQ_INSERT_TAIL(&dev->ipmi_completed_requests, req, ir_link);
		selwakeup(&dev->ipmi_select);
		if (dev->ipmi_closing)
			wakeup(&dev->ipmi_requests);
	}
}