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
typedef  int u_int32_t ;
struct sc_info {scalar_t__ which; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ASSP_0_WS_ENABLE ; 
 int ASSP_CLK_49MHZ_SELECT ; 
 int /*<<< orphan*/  ASSP_CONTROL_A ; 
 int /*<<< orphan*/  ASSP_CONTROL_B ; 
 int CLK_DIV_BY_49 ; 
 int CLK_MULT_MODE_SELECT ; 
 int CLK_MULT_MODE_SELECT_2 ; 
 int DSP_CLK_36MHZ_SELECT ; 
 scalar_t__ ESS_ALLEGRO_1 ; 
 scalar_t__ ESS_MAESTRO3 ; 
 int HV_BUTTON_FROM_GD ; 
 int HV_CTRL_ENABLE ; 
 int INT_CLK_MULT_ENABLE ; 
 int INT_CLK_SELECT ; 
 int INT_CLK_SRC_NOT_PCI ; 
 int IN_CLK_12MHZ_SELECT ; 
 int /*<<< orphan*/  M3_LOCK (struct sc_info*) ; 
 int /*<<< orphan*/  M3_LOCK_ASSERT (struct sc_info*) ; 
 int /*<<< orphan*/  M3_UNLOCK (struct sc_info*) ; 
 int /*<<< orphan*/  PCI_ALLEGRO_CONFIG ; 
 int /*<<< orphan*/  PCI_USER_CONFIG ; 
 int PM_CTRL_ENABLE ; 
 int REDUCED_DEBOUNCE ; 
 int RESET_ASSP ; 
 int RUN_ASSP ; 
 int USE_PCI_TIMING ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int m3_rd_1 (struct sc_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m3_wr_1 (struct sc_info*,int /*<<< orphan*/ ,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static void
m3_config(struct sc_info *sc)
{
	u_int32_t data, hv_cfg;
	int hint;

	M3_LOCK_ASSERT(sc);

	M3_UNLOCK(sc);
	/*
	 * The volume buttons can be wired up via two different sets of pins.
	 * This presents a problem since we can't tell which way it's
	 * configured.  Allow the user to set a hint in order to twiddle
	 * the proper bits.
	 */
	if (resource_int_value(device_get_name(sc->dev),
	                       device_get_unit(sc->dev),
			       "hwvol_config", &hint) == 0)
		hv_cfg = (hint > 0) ? HV_BUTTON_FROM_GD : 0;
	else
		hv_cfg = HV_BUTTON_FROM_GD;
	M3_LOCK(sc);

	data = pci_read_config(sc->dev, PCI_ALLEGRO_CONFIG, 4);
	data &= ~HV_BUTTON_FROM_GD;
	data |= REDUCED_DEBOUNCE | HV_CTRL_ENABLE | hv_cfg;
	data |= PM_CTRL_ENABLE | CLK_DIV_BY_49 | USE_PCI_TIMING;
	pci_write_config(sc->dev, PCI_ALLEGRO_CONFIG, data, 4);

	m3_wr_1(sc, ASSP_CONTROL_B, RESET_ASSP);
	data = pci_read_config(sc->dev, PCI_ALLEGRO_CONFIG, 4);
	data &= ~INT_CLK_SELECT;
	if (sc->which == ESS_MAESTRO3) {
		data &= ~INT_CLK_MULT_ENABLE;
		data |= INT_CLK_SRC_NOT_PCI;
	}
	data &= ~(CLK_MULT_MODE_SELECT | CLK_MULT_MODE_SELECT_2);
	pci_write_config(sc->dev, PCI_ALLEGRO_CONFIG, data, 4);

	if (sc->which == ESS_ALLEGRO_1) {
		data = pci_read_config(sc->dev, PCI_USER_CONFIG, 4);
		data |= IN_CLK_12MHZ_SELECT;
		pci_write_config(sc->dev, PCI_USER_CONFIG, data, 4);
	}

	data = m3_rd_1(sc, ASSP_CONTROL_A);
	data &= ~(DSP_CLK_36MHZ_SELECT | ASSP_CLK_49MHZ_SELECT);
	data |= ASSP_CLK_49MHZ_SELECT; /*XXX assumes 49MHZ dsp XXX*/
	data |= ASSP_0_WS_ENABLE;
	m3_wr_1(sc, ASSP_CONTROL_A, data);

	m3_wr_1(sc, ASSP_CONTROL_B, RUN_ASSP);
}