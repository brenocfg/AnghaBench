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
typedef  int uint16_t ;
struct usb_ether {int /*<<< orphan*/  ue_dev; } ;
struct axe_softc {int /*<<< orphan*/  sc_phyno; struct usb_ether sc_ue; } ;

/* Variables and functions */
 int AXE_178_RESET_MAGIC ; 
 int /*<<< orphan*/  AXE_CMD_RXCTL_WRITE ; 
 int /*<<< orphan*/  AXE_CMD_SROM_READ ; 
 int /*<<< orphan*/  AXE_CMD_SROM_WR_DISABLE ; 
 int /*<<< orphan*/  AXE_CMD_SROM_WR_ENABLE ; 
 int /*<<< orphan*/  AXE_CMD_SW_PHY_SELECT ; 
 int /*<<< orphan*/  AXE_CMD_SW_RESET_REG ; 
 int AXE_GPIO0 ; 
 int AXE_GPIO0_EN ; 
 int AXE_GPIO1 ; 
 int AXE_GPIO1_EN ; 
 int AXE_GPIO2 ; 
 int AXE_GPIO2_EN ; 
 int AXE_GPIO_RELOAD_EEPROM ; 
 int /*<<< orphan*/  AXE_GPIO_WRITE (int,int) ; 
#define  AXE_PHY_MODE_AGERE 135 
#define  AXE_PHY_MODE_CICADA 134 
#define  AXE_PHY_MODE_CICADA_V2 133 
#define  AXE_PHY_MODE_CICADA_V2_ASIX 132 
#define  AXE_PHY_MODE_MARVELL 131 
#define  AXE_PHY_MODE_REALTEK_8211BN 130 
#define  AXE_PHY_MODE_REALTEK_8211CL 129 
#define  AXE_PHY_MODE_REALTEK_8251CL 128 
 int AXE_SW_RESET_CLEAR ; 
 int AXE_SW_RESET_PRL ; 
 int /*<<< orphan*/  axe_cmd (struct axe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int axe_miibus_readreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  axe_miibus_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int hz ; 
 int le16toh (int) ; 
 int /*<<< orphan*/  uether_pause (struct usb_ether*,int) ; 

__attribute__((used)) static void
axe_ax88178_init(struct axe_softc *sc)
{
	struct usb_ether *ue;
	int gpio0, ledmode, phymode;
	uint16_t eeprom, val;

	ue = &sc->sc_ue;
	axe_cmd(sc, AXE_CMD_SROM_WR_ENABLE, 0, 0, NULL);
	/* XXX magic */
	axe_cmd(sc, AXE_CMD_SROM_READ, 0, 0x0017, &eeprom);
	eeprom = le16toh(eeprom);
	axe_cmd(sc, AXE_CMD_SROM_WR_DISABLE, 0, 0, NULL);

	/* if EEPROM is invalid we have to use to GPIO0 */
	if (eeprom == 0xffff) {
		phymode = AXE_PHY_MODE_MARVELL;
		gpio0 = 1;
		ledmode = 0;
	} else {
		phymode = eeprom & 0x7f;
		gpio0 = (eeprom & 0x80) ? 0 : 1;
		ledmode = eeprom >> 8;
	}

	if (bootverbose)
		device_printf(sc->sc_ue.ue_dev,
		    "EEPROM data : 0x%04x, phymode : 0x%02x\n", eeprom,
		    phymode);
	/* Program GPIOs depending on PHY hardware. */
	switch (phymode) {
	case AXE_PHY_MODE_MARVELL:
		if (gpio0 == 1) {
			AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM | AXE_GPIO0_EN,
			    hz / 32);
			AXE_GPIO_WRITE(AXE_GPIO0_EN | AXE_GPIO2 | AXE_GPIO2_EN,
			    hz / 32);
			AXE_GPIO_WRITE(AXE_GPIO0_EN | AXE_GPIO2_EN, hz / 4);
			AXE_GPIO_WRITE(AXE_GPIO0_EN | AXE_GPIO2 | AXE_GPIO2_EN,
			    hz / 32);
		} else {
			AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM | AXE_GPIO1 |
			    AXE_GPIO1_EN, hz / 3);
			if (ledmode == 1) {
				AXE_GPIO_WRITE(AXE_GPIO1_EN, hz / 3);
				AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN,
				    hz / 3);
			} else {
				AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN |
				    AXE_GPIO2 | AXE_GPIO2_EN, hz / 32);
				AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN |
				    AXE_GPIO2_EN, hz / 4);
				AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN |
				    AXE_GPIO2 | AXE_GPIO2_EN, hz / 32);
			}
		}
		break;
	case AXE_PHY_MODE_CICADA:
	case AXE_PHY_MODE_CICADA_V2:
	case AXE_PHY_MODE_CICADA_V2_ASIX:
		if (gpio0 == 1)
			AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM | AXE_GPIO0 |
			    AXE_GPIO0_EN, hz / 32);
		else
			AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM | AXE_GPIO1 |
			    AXE_GPIO1_EN, hz / 32);
		break;
	case AXE_PHY_MODE_AGERE:
		AXE_GPIO_WRITE(AXE_GPIO_RELOAD_EEPROM | AXE_GPIO1 |
		    AXE_GPIO1_EN, hz / 32);
		AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN | AXE_GPIO2 |
		    AXE_GPIO2_EN, hz / 32);
		AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN | AXE_GPIO2_EN, hz / 4);
		AXE_GPIO_WRITE(AXE_GPIO1 | AXE_GPIO1_EN | AXE_GPIO2 |
		    AXE_GPIO2_EN, hz / 32);
		break;
	case AXE_PHY_MODE_REALTEK_8211CL:
	case AXE_PHY_MODE_REALTEK_8211BN:
	case AXE_PHY_MODE_REALTEK_8251CL:
		val = gpio0 == 1 ? AXE_GPIO0 | AXE_GPIO0_EN :
		    AXE_GPIO1 | AXE_GPIO1_EN;
		AXE_GPIO_WRITE(val, hz / 32);
		AXE_GPIO_WRITE(val | AXE_GPIO2 | AXE_GPIO2_EN, hz / 32);
		AXE_GPIO_WRITE(val | AXE_GPIO2_EN, hz / 4);
		AXE_GPIO_WRITE(val | AXE_GPIO2 | AXE_GPIO2_EN, hz / 32);
		if (phymode == AXE_PHY_MODE_REALTEK_8211CL) {
			axe_miibus_writereg(ue->ue_dev, sc->sc_phyno,
			    0x1F, 0x0005);
			axe_miibus_writereg(ue->ue_dev, sc->sc_phyno,
			    0x0C, 0x0000);
			val = axe_miibus_readreg(ue->ue_dev, sc->sc_phyno,
			    0x0001);
			axe_miibus_writereg(ue->ue_dev, sc->sc_phyno,
			    0x01, val | 0x0080);
			axe_miibus_writereg(ue->ue_dev, sc->sc_phyno,
			    0x1F, 0x0000);
		}
		break;
	default:
		/* Unknown PHY model or no need to program GPIOs. */
		break;
	}

	/* soft reset */
	axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0, AXE_SW_RESET_CLEAR, NULL);
	uether_pause(ue, hz / 4);

	axe_cmd(sc, AXE_CMD_SW_RESET_REG, 0,
	    AXE_SW_RESET_PRL | AXE_178_RESET_MAGIC, NULL);
	uether_pause(ue, hz / 4);
	/* Enable MII/GMII/RGMII interface to work with external PHY. */
	axe_cmd(sc, AXE_CMD_SW_PHY_SELECT, 0, 0, NULL);
	uether_pause(ue, hz / 4);

	axe_cmd(sc, AXE_CMD_RXCTL_WRITE, 0, 0, NULL);
}