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
struct ipmi_softc {int /*<<< orphan*/  ipmi_request_added; int /*<<< orphan*/  ipmi_pending_requests; } ;
struct ipmi_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_LOCK_ASSERT (struct ipmi_softc*) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ipmi_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ir_link ; 

int
ipmi_polled_enqueue_request(struct ipmi_softc *sc, struct ipmi_request *req)
{

	IPMI_LOCK_ASSERT(sc);

	TAILQ_INSERT_TAIL(&sc->ipmi_pending_requests, req, ir_link);
	cv_signal(&sc->ipmi_request_added);
	return (0);
}