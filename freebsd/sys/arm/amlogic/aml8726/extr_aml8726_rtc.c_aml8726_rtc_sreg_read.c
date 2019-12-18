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
 int /*<<< orphan*/  aml8726_rtc_recv_data (struct aml8726_rtc_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aml8726_rtc_send_addr (struct aml8726_rtc_softc*,int) ; 
 int aml8726_rtc_start_transfer (struct aml8726_rtc_softc*) ; 

__attribute__((used)) static int
aml8726_rtc_sreg_read(struct aml8726_rtc_softc *sc, u_char sreg, uint32_t *val)
{
	u_char addr;
	int error;

	/* read is indicated by lsb = 0 */
	addr = (sreg << 1) | 0;

	error = aml8726_rtc_start_transfer(sc);

	if (error)
		return (error);

	aml8726_rtc_send_addr(sc, addr);
	aml8726_rtc_recv_data(sc, val);

	return (0);
}