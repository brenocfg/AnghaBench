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
struct adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_LOCK (struct adapter*) ; 
 int /*<<< orphan*/  ADAPTER_UNLOCK (struct adapter*) ; 
 int /*<<< orphan*/  ADAP_ERR ; 
 int /*<<< orphan*/  ASSERT_SYNCHRONIZED_OP (struct adapter*) ; 
 int /*<<< orphan*/  LOG_ALERT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct adapter*) ; 
 int /*<<< orphan*/  delayed_panic ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_callout ; 
 int hz ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ t4_panic_on_fatal_err ; 
 int /*<<< orphan*/  t4_shutdown_adapter (struct adapter*) ; 

void
t4_fatal_err(struct adapter *sc, bool fw_error)
{

	t4_shutdown_adapter(sc);
	log(LOG_ALERT, "%s: encountered fatal error, adapter stopped.\n",
	    device_get_nameunit(sc->dev));
	if (fw_error) {
		ASSERT_SYNCHRONIZED_OP(sc);
		sc->flags |= ADAP_ERR;
	} else {
		ADAPTER_LOCK(sc);
		sc->flags |= ADAP_ERR;
		ADAPTER_UNLOCK(sc);
	}

	if (t4_panic_on_fatal_err) {
		log(LOG_ALERT, "%s: panic on fatal error after 30s",
		    device_get_nameunit(sc->dev));
		callout_reset(&fatal_callout, hz * 30, delayed_panic, sc);
	}
}