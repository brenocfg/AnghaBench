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
struct hdac_softc {scalar_t__ polling; int /*<<< orphan*/  poll_ival; int /*<<< orphan*/  poll_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct hdac_softc*) ; 
 int /*<<< orphan*/  hdac_intr_handler (struct hdac_softc*) ; 
 int /*<<< orphan*/  hdac_lock (struct hdac_softc*) ; 
 int /*<<< orphan*/  hdac_unlock (struct hdac_softc*) ; 

__attribute__((used)) static void
hdac_poll_callback(void *arg)
{
	struct hdac_softc *sc = arg;

	if (sc == NULL)
		return;

	hdac_lock(sc);
	if (sc->polling == 0) {
		hdac_unlock(sc);
		return;
	}
	callout_reset(&sc->poll_callout, sc->poll_ival,
	    hdac_poll_callback, sc);
	hdac_unlock(sc);

	hdac_intr_handler(sc);
}