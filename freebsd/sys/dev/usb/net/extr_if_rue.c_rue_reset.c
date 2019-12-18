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
struct TYPE_2__ {int /*<<< orphan*/  ue_dev; } ;
struct rue_softc {TYPE_1__ sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUE_CR ; 
 int RUE_CR_SOFT_RST ; 
 int RUE_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int hz ; 
 int rue_csr_read_1 (struct rue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rue_csr_write_1 (struct rue_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uether_pause (TYPE_1__*,int) ; 

__attribute__((used)) static void
rue_reset(struct rue_softc *sc)
{
	int i;

	rue_csr_write_1(sc, RUE_CR, RUE_CR_SOFT_RST);

	for (i = 0; i != RUE_TIMEOUT; i++) {
		if (uether_pause(&sc->sc_ue, hz / 1000))
			break;
		if (!(rue_csr_read_1(sc, RUE_CR) & RUE_CR_SOFT_RST))
			break;
	}
	if (i == RUE_TIMEOUT)
		device_printf(sc->sc_ue.ue_dev, "reset never completed\n");

	uether_pause(&sc->sc_ue, hz / 100);
}