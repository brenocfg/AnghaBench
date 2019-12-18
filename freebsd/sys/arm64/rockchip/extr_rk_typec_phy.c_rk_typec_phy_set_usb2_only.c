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
struct rk_typec_phy_softc {int /*<<< orphan*/  phy_ctrl_id; int /*<<< orphan*/  grf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRF_USB3OTG_CON1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GRF_USB3PHY_CON0 (int /*<<< orphan*/ ) ; 
 int SYSCON_READ_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCON_WRITE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int USB3OTG_CON1_U3_DIS ; 
 int USB3PHY_CON0_USB2_ONLY ; 

__attribute__((used)) static void
rk_typec_phy_set_usb2_only(struct rk_typec_phy_softc *sc, bool usb2only)
{
	uint32_t reg;

	/* Disable usb3tousb2 only */
	reg = SYSCON_READ_4(sc->grf, GRF_USB3PHY_CON0(sc->phy_ctrl_id));
	if (usb2only)
		reg |= USB3PHY_CON0_USB2_ONLY;
	else
		reg &= ~USB3PHY_CON0_USB2_ONLY;
	/* Write Mask */
	reg |= (USB3PHY_CON0_USB2_ONLY) << 16;
	SYSCON_WRITE_4(sc->grf, GRF_USB3PHY_CON0(sc->phy_ctrl_id), reg);

	/* Enable the USB3 Super Speed port */
	reg = SYSCON_READ_4(sc->grf, GRF_USB3OTG_CON1(sc->phy_ctrl_id));
	if (usb2only)
		reg |= USB3OTG_CON1_U3_DIS;
	else
		reg &= ~USB3OTG_CON1_U3_DIS;
	/* Write Mask */
	reg |= (USB3OTG_CON1_U3_DIS) << 16;
	SYSCON_WRITE_4(sc->grf, GRF_USB3OTG_CON1(sc->phy_ctrl_id), reg);
}