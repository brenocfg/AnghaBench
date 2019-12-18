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
typedef  int /*<<< orphan*/  uint8_t ;
struct tps65217_status_reg {int acpwr; scalar_t__ pb; } ;
struct tps65217_int_reg {scalar_t__ aci; scalar_t__ pbi; } ;
struct am335x_pmic_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  notify_buf ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  RB_POWEROFF ; 
 int /*<<< orphan*/  THREAD_NO_SLEEPING () ; 
 int /*<<< orphan*/  THREAD_SLEEPING_OK () ; 
 int /*<<< orphan*/  TPS65217_INT_REG ; 
 int /*<<< orphan*/  TPS65217_STATUS_REG ; 
 int am335x_pmic_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devctl_notify_f (char*,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  shutdown_nice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
am335x_pmic_intr(void *arg)
{
	struct am335x_pmic_softc *sc = (struct am335x_pmic_softc *)arg;
	struct tps65217_status_reg status_reg;
	struct tps65217_int_reg int_reg;
	int rv;
	char notify_buf[16];

	THREAD_SLEEPING_OK();
	rv = am335x_pmic_read(sc->sc_dev, TPS65217_INT_REG, (uint8_t *)&int_reg, 1);
	if (rv != 0) {
		device_printf(sc->sc_dev, "Cannot read interrupt register\n");
		THREAD_NO_SLEEPING();
		return;
	}
	rv = am335x_pmic_read(sc->sc_dev, TPS65217_STATUS_REG, (uint8_t *)&status_reg, 1);
	if (rv != 0) {
		device_printf(sc->sc_dev, "Cannot read status register\n");
		THREAD_NO_SLEEPING();
		return;
	}
	THREAD_NO_SLEEPING();

	if (int_reg.pbi && status_reg.pb)
		shutdown_nice(RB_POWEROFF);
	if (int_reg.aci) {
		snprintf(notify_buf, sizeof(notify_buf), "notify=0x%02x",
		    status_reg.acpwr);
		devctl_notify_f("ACPI", "ACAD", "power", notify_buf, M_NOWAIT);
	}
}