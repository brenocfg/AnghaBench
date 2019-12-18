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
struct rum_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  RT2573_MAC_CSR12 ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 scalar_t__ rum_pause (struct rum_softc*,int) ; 
 int rum_read (struct rum_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rum_write (struct rum_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
rum_bbp_wakeup(struct rum_softc *sc)
{
	unsigned int ntries;

	for (ntries = 0; ntries < 100; ntries++) {
		if (rum_read(sc, RT2573_MAC_CSR12) & 8)
			break;
		rum_write(sc, RT2573_MAC_CSR12, 4);	/* force wakeup */
		if (rum_pause(sc, hz / 100))
			break;
	}
	if (ntries == 100) {
		device_printf(sc->sc_dev,
		    "timeout waiting for BBP/RF to wakeup\n");
		return (ETIMEDOUT);
	}

	return (0);
}