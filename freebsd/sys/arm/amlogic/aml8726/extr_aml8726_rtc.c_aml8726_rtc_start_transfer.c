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
struct aml8726_rtc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_RTC_0_REG ; 
 int /*<<< orphan*/  AML_RTC_1_REG ; 
 int AML_RTC_SCLK ; 
 int AML_RTC_SDI ; 
 int AML_RTC_SEN ; 
 int AML_RTC_SRDY ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_rtc_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct aml8726_rtc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_rtc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 

__attribute__((used)) static int
aml8726_rtc_start_transfer(struct aml8726_rtc_softc *sc)
{
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

	if (i == 0)
		return (EIO);

	/* start the cycle */
	CSR_WRITE_4(sc, AML_RTC_0_REG, (CSR_READ_4(sc, AML_RTC_0_REG) |
	    AML_RTC_SEN));

	return (0);
}