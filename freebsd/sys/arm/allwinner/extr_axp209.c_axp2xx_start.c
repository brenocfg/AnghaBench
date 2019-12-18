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
typedef  int uint8_t ;
struct axp2xx_softc {int nsensors; int /*<<< orphan*/  intr_hook; int /*<<< orphan*/  intrcookie; int /*<<< orphan*/ * res; TYPE_1__* sensors; void* dev; } ;
typedef  void* device_t ;
struct TYPE_2__ {int enable_mask; int /*<<< orphan*/  desc; int /*<<< orphan*/  format; int /*<<< orphan*/  id; int /*<<< orphan*/  name; int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int AXP2XX_IRQ1_AC_CONN ; 
 int AXP2XX_IRQ1_AC_DISCONN ; 
 int AXP2XX_IRQ1_AC_OVERVOLT ; 
 int /*<<< orphan*/  AXP2XX_IRQ1_ENABLE ; 
 int AXP2XX_IRQ1_VBUS_CONN ; 
 int AXP2XX_IRQ1_VBUS_DISCONN ; 
 int AXP2XX_IRQ1_VBUS_OVERVOLT ; 
 int AXP2XX_IRQ2_BATT_CHARGED ; 
 int AXP2XX_IRQ2_BATT_CHARGE_ACCT_OFF ; 
 int AXP2XX_IRQ2_BATT_CHARGE_ACCT_ON ; 
 int AXP2XX_IRQ2_BATT_CHARGING ; 
 int AXP2XX_IRQ2_BATT_CONN ; 
 int AXP2XX_IRQ2_BATT_DISCONN ; 
 int AXP2XX_IRQ2_BATT_TEMP_LOW ; 
 int AXP2XX_IRQ2_BATT_TEMP_OVER ; 
 int /*<<< orphan*/  AXP2XX_IRQ2_ENABLE ; 
 int /*<<< orphan*/  AXP2XX_IRQ3_ENABLE ; 
 int AXP2XX_IRQ3_PEK_LONG ; 
 int AXP2XX_IRQ3_PEK_SHORT ; 
 int AXP2XX_IRQ4_APS_LOW_2 ; 
 int /*<<< orphan*/  AXP2XX_IRQ4_ENABLE ; 
 int /*<<< orphan*/  AXP2XX_IRQ5_ENABLE ; 
 int /*<<< orphan*/  AXP2XX_PSR ; 
 int AXP2XX_PSR_ACIN ; 
 int AXP2XX_PSR_ACIN_SHIFT ; 
 int AXP2XX_PSR_VBUS ; 
 int AXP2XX_PSR_VBUS_SHIFT ; 
 int CTLFLAG_RD ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_LAST ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axp2xx_intr ; 
 int axp2xx_read (void*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  axp2xx_shutdown ; 
 int /*<<< orphan*/  axp2xx_sysctl ; 
 int axp2xx_write (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_setup_intr (void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct axp2xx_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct axp2xx_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (void*) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (void*) ; 
 int /*<<< orphan*/  device_printf (void*,char*,...) ; 
 int /*<<< orphan*/  shutdown_final ; 

__attribute__((used)) static void
axp2xx_start(void *pdev)
{
	device_t dev;
	struct axp2xx_softc *sc;
	const char *pwr_name[] = {"Battery", "AC", "USB", "AC and USB"};
	int i;
	uint8_t reg, data;
	uint8_t pwr_src;

	dev = pdev;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bootverbose) {
		/*
		 * Read the Power State register.
		 * Shift the AC presence into bit 0.
		 * Shift the Battery presence into bit 1.
		 */
		axp2xx_read(dev, AXP2XX_PSR, &data, 1);
		pwr_src = ((data & AXP2XX_PSR_ACIN) >> AXP2XX_PSR_ACIN_SHIFT) |
		    ((data & AXP2XX_PSR_VBUS) >> (AXP2XX_PSR_VBUS_SHIFT - 1));

		device_printf(dev, "Powered by %s\n",
		    pwr_name[pwr_src]);
	}

	/* Only enable interrupts that we are interested in */
	axp2xx_write(dev, AXP2XX_IRQ1_ENABLE,
	    AXP2XX_IRQ1_AC_OVERVOLT |
	    AXP2XX_IRQ1_AC_DISCONN |
	    AXP2XX_IRQ1_AC_CONN |
	    AXP2XX_IRQ1_VBUS_OVERVOLT |
	    AXP2XX_IRQ1_VBUS_DISCONN |
	    AXP2XX_IRQ1_VBUS_CONN);
	axp2xx_write(dev, AXP2XX_IRQ2_ENABLE,
	    AXP2XX_IRQ2_BATT_CONN |
	    AXP2XX_IRQ2_BATT_DISCONN |
	    AXP2XX_IRQ2_BATT_CHARGE_ACCT_ON |
	    AXP2XX_IRQ2_BATT_CHARGE_ACCT_OFF |
	    AXP2XX_IRQ2_BATT_CHARGING |
	    AXP2XX_IRQ2_BATT_CHARGED |
	    AXP2XX_IRQ2_BATT_TEMP_OVER |
	    AXP2XX_IRQ2_BATT_TEMP_LOW);
	axp2xx_write(dev, AXP2XX_IRQ3_ENABLE,
	    AXP2XX_IRQ3_PEK_SHORT | AXP2XX_IRQ3_PEK_LONG);
	axp2xx_write(dev, AXP2XX_IRQ4_ENABLE, AXP2XX_IRQ4_APS_LOW_2);
	axp2xx_write(dev, AXP2XX_IRQ5_ENABLE, 0x0);

	EVENTHANDLER_REGISTER(shutdown_final, axp2xx_shutdown, dev,
	    SHUTDOWN_PRI_LAST);

	/* Enable ADC sensors */
	for (i = 0; i < sc->nsensors; i++) {
		if (axp2xx_read(dev, sc->sensors[i].enable_reg, &reg, 1) == -1) {
			device_printf(dev, "Cannot enable sensor '%s'\n",
			    sc->sensors[i].name);
			continue;
		}
		reg |= sc->sensors[i].enable_mask;
		if (axp2xx_write(dev, sc->sensors[i].enable_reg, reg) == -1) {
			device_printf(dev, "Cannot enable sensor '%s'\n",
			    sc->sensors[i].name);
			continue;
		}
		SYSCTL_ADD_PROC(device_get_sysctl_ctx(dev),
		    SYSCTL_CHILDREN(device_get_sysctl_tree(dev)),
		    OID_AUTO, sc->sensors[i].name,
		    CTLTYPE_INT | CTLFLAG_RD,
		    dev, sc->sensors[i].id, axp2xx_sysctl,
		    sc->sensors[i].format,
		    sc->sensors[i].desc);
	}

	if ((bus_setup_intr(dev, sc->res[0], INTR_TYPE_MISC | INTR_MPSAFE,
	      NULL, axp2xx_intr, sc, &sc->intrcookie)))
		device_printf(dev, "unable to register interrupt handler\n");

	config_intrhook_disestablish(&sc->intr_hook);
}