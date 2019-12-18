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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_char ;
struct aml8726_rtc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  aml8726_rtc_send_addr (struct aml8726_rtc_softc*,int) ; 
 int /*<<< orphan*/  aml8726_rtc_send_data (struct aml8726_rtc_softc*,int /*<<< orphan*/ ) ; 
 int aml8726_rtc_start_transfer (struct aml8726_rtc_softc*) ; 

__attribute__((used)) static int
aml8726_rtc_sreg_write(struct aml8726_rtc_softc *sc, u_char sreg, uint32_t val)
{
	u_char addr;
	int error;

	/* write is indicated by lsb = 1 */
	addr = (sreg << 1) | 1;

	error = aml8726_rtc_start_transfer(sc);

	if (error)
		return (error);

	aml8726_rtc_send_data(sc, val);
	aml8726_rtc_send_addr(sc, addr);

	return (0);
}