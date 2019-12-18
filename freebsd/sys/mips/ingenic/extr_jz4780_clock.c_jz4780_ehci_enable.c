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
struct jz4780_clock_softc {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGU_LOCK (struct jz4780_clock_softc*) ; 
 int /*<<< orphan*/  CGU_UNLOCK (struct jz4780_clock_softc*) ; 
 int CSR_READ_4 (struct jz4780_clock_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jz4780_clock_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  JZ_OPCR ; 
 int /*<<< orphan*/  JZ_SRBC ; 
 int /*<<< orphan*/  JZ_USBPCR ; 
 int /*<<< orphan*/  JZ_USBPCR1 ; 
 int OPCR_SPENDN1 ; 
 int PCR_DMPD1 ; 
 int PCR_DPPD1 ; 
 int PCR_OTG_DISABLE ; 
 int PCR_POR ; 
 int PCR_WORD_I_F0 ; 
 int PCR_WORD_I_F1 ; 
 int SRBC_UHC_SR ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jz4780_clock_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int hz ; 
 int /*<<< orphan*/  jz4780_clock_devclass ; 
 scalar_t__ jz4780_ehci_clk_config (struct jz4780_clock_softc*) ; 

int
jz4780_ehci_enable(void)
{
	device_t dev;
	struct jz4780_clock_softc *sc;
	uint32_t reg;

	dev = devclass_get_device(jz4780_clock_devclass, 0);
	if (dev == NULL)
		return (-1);

	sc = device_get_softc(dev);

	/*
	 * EHCI should use MPPL as a parent, but Linux configures OTG
	 * clock anyway. Follow their lead blindly.
	 */
	if (jz4780_ehci_clk_config(sc) != 0)
		return (-1);

	CGU_LOCK(sc);

	/* Enable OTG, should not be necessary since we use PLL clock */
	reg = CSR_READ_4(sc, JZ_USBPCR);
	reg &= ~(PCR_OTG_DISABLE);
	CSR_WRITE_4(sc, JZ_USBPCR, reg);

	/* Do not force port1 to suspend mode */
	reg = CSR_READ_4(sc, JZ_OPCR);
	reg |= OPCR_SPENDN1;
	CSR_WRITE_4(sc, JZ_OPCR, reg);

	/* D- pulldown */
	reg = CSR_READ_4(sc, JZ_USBPCR1);
	reg |= PCR_DMPD1;
	CSR_WRITE_4(sc, JZ_USBPCR1, reg);

	/* D+ pulldown */
	reg = CSR_READ_4(sc, JZ_USBPCR1);
	reg |= PCR_DPPD1;
	CSR_WRITE_4(sc, JZ_USBPCR1, reg);

	/* 16 bit bus witdth for port 1*/
	reg = CSR_READ_4(sc, JZ_USBPCR1);
	reg |= PCR_WORD_I_F1 | PCR_WORD_I_F0;
	CSR_WRITE_4(sc, JZ_USBPCR1, reg);

	/* Reset USB */
	reg = CSR_READ_4(sc, JZ_USBPCR);
	reg |= PCR_POR;
	CSR_WRITE_4(sc, JZ_USBPCR, reg);
	DELAY(1);
	reg = CSR_READ_4(sc, JZ_USBPCR);
	reg &= ~(PCR_POR);
	CSR_WRITE_4(sc, JZ_USBPCR, reg);

	/* Soft-reset USB */
	reg = CSR_READ_4(sc, JZ_SRBC);
	reg |= SRBC_UHC_SR;
	CSR_WRITE_4(sc, JZ_SRBC, reg);
	/* 300ms */
	DELAY(300*hz/1000);

	reg = CSR_READ_4(sc, JZ_SRBC);
	reg &= ~(SRBC_UHC_SR);
	CSR_WRITE_4(sc, JZ_SRBC, reg);

	/* 300ms */
	DELAY(300*hz/1000);

	CGU_UNLOCK(sc);
	return (0);
}