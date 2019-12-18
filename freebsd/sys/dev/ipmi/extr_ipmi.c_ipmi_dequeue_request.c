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
struct ipmi_softc {int /*<<< orphan*/  ipmi_pending_requests; scalar_t__ ipmi_detaching; int /*<<< orphan*/  ipmi_requests_lock; int /*<<< orphan*/  ipmi_request_added; } ;
struct ipmi_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_LOCK_ASSERT (struct ipmi_softc*) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct ipmi_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ipmi_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ir_link ; 

struct ipmi_request *
ipmi_dequeue_request(struct ipmi_softc *sc)
{
	struct ipmi_request *req;

	IPMI_LOCK_ASSERT(sc);

	while (!sc->ipmi_detaching && TAILQ_EMPTY(&sc->ipmi_pending_requests))
		cv_wait(&sc->ipmi_request_added, &sc->ipmi_requests_lock);
	if (sc->ipmi_detaching)
		return (NULL);

	req = TAILQ_FIRST(&sc->ipmi_pending_requests);
	TAILQ_REMOVE(&sc->ipmi_pending_requests, req, ir_link);
	return (req);
}