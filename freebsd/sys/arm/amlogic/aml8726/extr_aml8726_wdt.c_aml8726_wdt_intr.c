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
struct aml8726_wdt_softc {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AML_WDT_CTRL_EN ; 
 int AML_WDT_CTRL_IRQ_EN ; 
 int /*<<< orphan*/  AML_WDT_CTRL_REG ; 
 int /*<<< orphan*/  AML_WDT_LOCK (struct aml8726_wdt_softc*) ; 
 int /*<<< orphan*/  AML_WDT_UNLOCK (struct aml8726_wdt_softc*) ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_wdt_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct aml8726_wdt_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_wdt_softc*,int /*<<< orphan*/ ,int) ; 
 int FILTER_HANDLED ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
aml8726_wdt_intr(void *arg)
{
	struct aml8726_wdt_softc *sc = (struct aml8726_wdt_softc *)arg;

	/*
	 * Normally a timeout causes a hardware reset, however
	 * the watchdog timer can be configured to cause an
	 * interrupt instead by setting AML_WDT_CTRL_IRQ_EN
	 * and clearing AML_WDT_CTRL_CPU_WDRESET_MASK.
	 */

	AML_WDT_LOCK(sc);

	CSR_WRITE_4(sc, AML_WDT_CTRL_REG,
	    (CSR_READ_4(sc, AML_WDT_CTRL_REG) & ~(AML_WDT_CTRL_IRQ_EN |
	    AML_WDT_CTRL_EN)));

	CSR_BARRIER(sc, AML_WDT_CTRL_REG);

	AML_WDT_UNLOCK(sc);

	device_printf(sc->dev, "timeout expired\n");

	return (FILTER_HANDLED);
}