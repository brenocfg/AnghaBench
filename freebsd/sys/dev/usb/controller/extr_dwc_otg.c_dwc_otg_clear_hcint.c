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
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct dwc_otg_softc {TYPE_1__* sc_chan_state; } ;
struct TYPE_2__ {scalar_t__ hcint; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOTG_HCINT (size_t) ; 
 int /*<<< orphan*/  DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwc_otg_clear_hcint(struct dwc_otg_softc *sc, uint8_t x)
{
	uint32_t hcint;

	/* clear all pending interrupts */
	hcint = DWC_OTG_READ_4(sc, DOTG_HCINT(x));
	DWC_OTG_WRITE_4(sc, DOTG_HCINT(x), hcint);

	/* clear buffered interrupts */
	sc->sc_chan_state[x].hcint = 0;
}