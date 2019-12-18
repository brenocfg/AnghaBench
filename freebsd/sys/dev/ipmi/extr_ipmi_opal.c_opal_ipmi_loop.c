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
struct opal_ipmi_softc {int /*<<< orphan*/  ipmi; } ;
struct ipmi_request {scalar_t__ ir_error; } ;

/* Variables and functions */
 scalar_t__ EIO ; 
 int /*<<< orphan*/  IPMI_IO_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPMI_IO_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPMI_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPMI_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAX_TIMEOUT ; 
 int /*<<< orphan*/  ipmi_complete_request (int /*<<< orphan*/ *,struct ipmi_request*) ; 
 struct ipmi_request* ipmi_dequeue_request (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int opal_ipmi_polled_request (struct opal_ipmi_softc*,struct ipmi_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
opal_ipmi_loop(void *arg)
{
	struct opal_ipmi_softc *sc = arg;
	struct ipmi_request *req;
	int i, ok;

	IPMI_LOCK(&sc->ipmi);
	while ((req = ipmi_dequeue_request(&sc->ipmi)) != NULL) {
		IPMI_UNLOCK(&sc->ipmi);
		ok = 0;
		for (i = 0; i < 3 && !ok; i++) {
			IPMI_IO_LOCK(&sc->ipmi);
			ok = opal_ipmi_polled_request(sc, req, MAX_TIMEOUT);
			IPMI_IO_UNLOCK(&sc->ipmi);
		}
		if (ok)
			req->ir_error = 0;
		else
			req->ir_error = EIO;
		IPMI_LOCK(&sc->ipmi);
		ipmi_complete_request(&sc->ipmi, req);
	}
	IPMI_UNLOCK(&sc->ipmi);
	kproc_exit(0);
}