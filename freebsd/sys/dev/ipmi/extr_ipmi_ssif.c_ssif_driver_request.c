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
struct ipmi_softc {int /*<<< orphan*/  ipmi_requests_lock; } ;
struct ipmi_request {int ir_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_LOCK (struct ipmi_softc*) ; 
 int /*<<< orphan*/  IPMI_UNLOCK (struct ipmi_softc*) ; 
 int ipmi_polled_enqueue_request (struct ipmi_softc*,struct ipmi_request*) ; 
 int msleep (struct ipmi_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
ssif_driver_request(struct ipmi_softc *sc, struct ipmi_request *req, int timo)
{
	int error;

	IPMI_LOCK(sc);
	error = ipmi_polled_enqueue_request(sc, req);
	if (error == 0)
		error = msleep(req, &sc->ipmi_requests_lock, 0, "ipmireq",
		    timo);
	if (error == 0)
		error = req->ir_error;
	IPMI_UNLOCK(sc);
	return (error);
}