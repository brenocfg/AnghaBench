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
 int AML_RTC_SCLK ; 
 int /*<<< orphan*/  CSR_BARRIER (struct aml8726_rtc_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct aml8726_rtc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_rtc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 

__attribute__((used)) static inline void
aml8726_rtc_sclk_pulse(struct aml8726_rtc_softc *sc)
{

	DELAY(5);

	CSR_WRITE_4(sc, AML_RTC_0_REG, (CSR_READ_4(sc, AML_RTC_0_REG) |
	    AML_RTC_SCLK));

	CSR_BARRIER(sc, AML_RTC_0_REG);

	DELAY(5);

	CSR_WRITE_4(sc, AML_RTC_0_REG, (CSR_READ_4(sc, AML_RTC_0_REG) &
	    ~AML_RTC_SCLK));

	CSR_BARRIER(sc, AML_RTC_0_REG);
}