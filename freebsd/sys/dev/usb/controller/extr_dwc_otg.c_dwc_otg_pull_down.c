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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ d_pulled_up; } ;
struct dwc_otg_softc {TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCTL_SFTDISCON ; 
 int /*<<< orphan*/  DOTG_DCTL ; 
 int /*<<< orphan*/  DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwc_otg_pull_down(struct dwc_otg_softc *sc)
{
	uint32_t temp;

	/* pulldown D+, if possible */

	if (sc->sc_flags.d_pulled_up) {
		sc->sc_flags.d_pulled_up = 0;

		temp = DWC_OTG_READ_4(sc, DOTG_DCTL);
		temp |= DCTL_SFTDISCON;
		DWC_OTG_WRITE_4(sc, DOTG_DCTL, temp);
	}
}