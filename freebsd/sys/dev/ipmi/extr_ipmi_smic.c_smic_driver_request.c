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
struct ipmi_request {int ir_error; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IPMI_IO_LOCK (struct ipmi_softc*) ; 
 int /*<<< orphan*/  IPMI_IO_UNLOCK (struct ipmi_softc*) ; 
 int smic_polled_request (struct ipmi_softc*,struct ipmi_request*) ; 

__attribute__((used)) static int
smic_driver_request(struct ipmi_softc *sc, struct ipmi_request *req, int timo)
{
	int i, ok;

	ok = 0;
	for (i = 0; i < 3 && !ok; i++) {
		IPMI_IO_LOCK(sc);
		ok = smic_polled_request(sc, req);
		IPMI_IO_UNLOCK(sc);
	}
	if (ok)
		req->ir_error = 0;
	else
		req->ir_error = EIO;
	return (req->ir_error);
}