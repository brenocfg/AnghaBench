#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int teardown; scalar_t__ running; } ;
struct cpsw_softc {TYPE_1__ rx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_CPDMA_RX_TEARDOWN ; 
 int /*<<< orphan*/  CPSW_DEBUGF (struct cpsw_softc*,char*) ; 
 int /*<<< orphan*/  CPSW_RX_LOCK (struct cpsw_softc*) ; 
 int /*<<< orphan*/  CPSW_RX_UNLOCK (struct cpsw_softc*) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  cpsw_write_4 (struct cpsw_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
cpsw_rx_teardown(struct cpsw_softc *sc)
{
	int i = 0;

	CPSW_RX_LOCK(sc);
	CPSW_DEBUGF(sc, ("starting RX teardown"));
	sc->rx.teardown = 1;
	cpsw_write_4(sc, CPSW_CPDMA_RX_TEARDOWN, 0);
	CPSW_RX_UNLOCK(sc);
	while (sc->rx.running) {
		if (++i > 10) {
			device_printf(sc->dev,
			    "Unable to cleanly shutdown receiver\n");
			return;
		}
		DELAY(200);
	}
	if (!sc->rx.running)
		CPSW_DEBUGF(sc, ("finished RX teardown (%d retries)", i));
}