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
typedef  int uint32_t ;
struct TYPE_2__ {scalar_t__ status_high_speed; } ;
struct dwc_otg_softc {TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOTG_HFIR ; 
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int DWC_OTG_READ_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int) ; 
 int HFIR_FRINT_MASK ; 

__attribute__((used)) static void
dwc_otg_update_host_frame_interval(struct dwc_otg_softc *sc)
{

  /*
   * Disabled until further. Assuming that the register is already
   * programmed correctly by the boot loader.
   */
#if 0
	uint32_t temp;

	/* setup HOST frame interval register, based on existing value */
	temp = DWC_OTG_READ_4(sc, DOTG_HFIR) & HFIR_FRINT_MASK;
	if (temp >= 10000)
		temp /= 1000;
	else
		temp /= 125;

	/* figure out nearest X-tal value */
	if (temp >= 54)
		temp = 60;	/* MHz */
	else if (temp >= 39)
		temp = 48;	/* MHz */
	else
		temp = 30;	/* MHz */

	if (sc->sc_flags.status_high_speed)
		temp *= 125;
	else
		temp *= 1000;

	DPRINTF("HFIR=0x%08x\n", temp);

	DWC_OTG_WRITE_4(sc, DOTG_HFIR, temp);
#endif
}