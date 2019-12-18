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
 int /*<<< orphan*/  JZ_USBPCR ; 
 int /*<<< orphan*/  JZ_USBPCR1 ; 
 int /*<<< orphan*/  JZ_USBRDT ; 
 int /*<<< orphan*/  JZ_USBVBFIL ; 
 int OPCR_SPENDN0 ; 
 int PCR_COMMONONN ; 
 int PCR_OTG_DISABLE ; 
 int PCR_POR ; 
 int PCR_SYNOPSYS ; 
 int PCR_USB_MODE ; 
 int PCR_VBUSVLDEXT ; 
 int PCR_VBUSVLDEXTSEL ; 
 int PCR_WORD_I_F0 ; 
 int PCR_WORD_I_F1 ; 
 int REG_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USBRDT_USBRDT ; 
 int USBRDT_VBFIL_LD_EN ; 
 int /*<<< orphan*/  USBRESET_DETECT_TIME ; 
 int /*<<< orphan*/  USBVBFIL_IDDIGFIL ; 
 int /*<<< orphan*/  USBVBFIL_USBVBFIL ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct jz4780_clock_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jz4780_clock_devclass ; 

int
jz4780_otg_enable(void)
{
	device_t dev;
	struct jz4780_clock_softc *sc;
	uint32_t reg;

	dev = devclass_get_device(jz4780_clock_devclass, 0);
	if (dev == NULL)
		return (-1);

	sc = device_get_softc(dev);

	CGU_LOCK(sc);

	/* Select Synopsys OTG mode */
	reg = CSR_READ_4(sc, JZ_USBPCR1);
	reg |= PCR_SYNOPSYS;

	/* Set UTMI bus width to 16 bit */
	reg |= PCR_WORD_I_F0 | PCR_WORD_I_F1;
	CSR_WRITE_4(sc, JZ_USBPCR1, reg);

	/* Blah */
	reg = CSR_READ_4(sc, JZ_USBVBFIL);
	reg = REG_SET(reg, USBVBFIL_IDDIGFIL, 0);
	reg = REG_SET(reg, USBVBFIL_USBVBFIL, 0);
	CSR_WRITE_4(sc, JZ_USBVBFIL, reg);

	/* Setup reset detect time */
	reg = CSR_READ_4(sc, JZ_USBRDT);
	reg = REG_SET(reg, USBRDT_USBRDT, USBRESET_DETECT_TIME);
	reg |= USBRDT_VBFIL_LD_EN;
	CSR_WRITE_4(sc, JZ_USBRDT, reg);

	/* Setup USBPCR bits */
	reg = CSR_READ_4(sc, JZ_USBPCR);
	reg |= PCR_USB_MODE;
	reg |= PCR_COMMONONN;
	reg |= PCR_VBUSVLDEXT;
	reg |= PCR_VBUSVLDEXTSEL;
	reg &= ~(PCR_OTG_DISABLE);
	CSR_WRITE_4(sc, JZ_USBPCR, reg);

	/* Reset USB */
	reg = CSR_READ_4(sc, JZ_USBPCR);
	reg |= PCR_POR;
	CSR_WRITE_4(sc, JZ_USBPCR, reg);
	DELAY(1000);
	reg = CSR_READ_4(sc, JZ_USBPCR);
	reg &= ~(PCR_POR);
	CSR_WRITE_4(sc, JZ_USBPCR, reg);

	/* Unsuspend OTG port */
	reg = CSR_READ_4(sc, JZ_OPCR);
	reg |= OPCR_SPENDN0;
	CSR_WRITE_4(sc, JZ_OPCR, reg);

	CGU_UNLOCK(sc);
	return (0);
}