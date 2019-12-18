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
typedef  int uint32_t ;
struct dwc_otg_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOTG_GRSTCTL ; 
 int DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int GRSTCTL_RXFFLSH ; 
 int GRSTCTL_TXFFLSH ; 

__attribute__((used)) static void
dwc_otg_tx_fifo_reset(struct dwc_otg_softc *sc, uint32_t value)
{
	uint32_t temp;

  	/* reset FIFO */
	DWC_OTG_WRITE_4(sc, DOTG_GRSTCTL, value);

	/* wait for reset to complete */
	for (temp = 0; temp != 16; temp++) {
		value = DWC_OTG_READ_4(sc, DOTG_GRSTCTL);
		if (!(value & (GRSTCTL_TXFFLSH | GRSTCTL_RXFFLSH)))
			break;
	}
}