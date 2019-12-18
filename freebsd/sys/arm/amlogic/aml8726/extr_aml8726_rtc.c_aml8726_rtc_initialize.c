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
struct TYPE_2__ {scalar_t__ always; int xo; int /*<<< orphan*/  gpo; } ;
struct aml8726_rtc_softc {TYPE_1__ init; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_RTC_0_REG ; 
 int /*<<< orphan*/  AML_RTC_1_REG ; 
 int /*<<< orphan*/  AML_RTC_4_REG ; 
 int AML_RTC_ABSY ; 
 int AML_RTC_AS ; 
 int /*<<< orphan*/  AML_RTC_GPO_SREG ; 
 int AML_RTC_IRQ_DIS ; 
 int AML_RTC_SCLK ; 
 int AML_RTC_SDI ; 
 int AML_RTC_SEN ; 
 int AML_RTC_SRDY ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_rtc_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct aml8726_rtc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_rtc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ TRUE ; 
 int aml8726_rtc_sreg_write (struct aml8726_rtc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 

__attribute__((used)) static int
aml8726_rtc_initialize(struct aml8726_rtc_softc *sc)
{
	int error;
	unsigned i;

	/* idle the serial interface */
	CSR_WRITE_4(sc, AML_RTC_0_REG, (CSR_READ_4(sc, AML_RTC_0_REG) &
	    ~(AML_RTC_SCLK | AML_RTC_SEN | AML_RTC_SDI)));

	CSR_BARRIER(sc, AML_RTC_0_REG);

	/* see if it is ready for a new cycle */
	for (i = 40; i; i--) {
		DELAY(5);
		if ( (CSR_READ_4(sc, AML_RTC_1_REG) & AML_RTC_SRDY) )
			break;
	}

	if (sc->init.always == TRUE || (CSR_READ_4(sc, AML_RTC_1_REG) &
	    AML_RTC_SRDY) == 0) {

		/*
		 * The RTC has a 16 bit initialization register.  The upper
		 * bits can be written directly.  The lower bits are written
		 * through a shift register.
		 */

		CSR_WRITE_4(sc, AML_RTC_4_REG, ((sc->init.xo >> 8) & 0xff));

		CSR_WRITE_4(sc, AML_RTC_0_REG,
		    ((CSR_READ_4(sc, AML_RTC_0_REG) & 0xffffff) |
		    ((uint32_t)(sc->init.xo & 0xff) << 24) | AML_RTC_AS |
		    AML_RTC_IRQ_DIS));

		while ((CSR_READ_4(sc, AML_RTC_0_REG) & AML_RTC_ABSY) != 0)
			cpu_spinwait();

		DELAY(2);

		error = aml8726_rtc_sreg_write(sc, AML_RTC_GPO_SREG,
		    sc->init.gpo);

		if (error)
			return (error);
	}

	return (0);
}