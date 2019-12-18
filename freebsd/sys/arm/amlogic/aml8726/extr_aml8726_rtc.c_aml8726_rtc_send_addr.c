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
typedef  unsigned int u_char ;
struct aml8726_rtc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AML_RTC_0_REG ; 
 int AML_RTC_SEN ; 
 int CSR_READ_4 (struct aml8726_rtc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct aml8726_rtc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aml8726_rtc_send_bit (struct aml8726_rtc_softc*,unsigned int) ; 

__attribute__((used)) static inline void
aml8726_rtc_send_addr(struct aml8726_rtc_softc *sc, u_char addr)
{
	unsigned mask;

	for (mask = 1 << 3; mask; mask >>= 1) {
		if (mask == 1) {
			/* final bit indicates read / write mode */
			CSR_WRITE_4(sc, AML_RTC_0_REG,
			    (CSR_READ_4(sc, AML_RTC_0_REG) & ~AML_RTC_SEN));
		}
		aml8726_rtc_send_bit(sc, (addr & mask));
	}
}