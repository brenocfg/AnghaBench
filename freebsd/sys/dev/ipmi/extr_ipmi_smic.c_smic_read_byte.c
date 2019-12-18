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
typedef  scalar_t__ u_char ;
struct ipmi_softc {int /*<<< orphan*/  ipmi_dev; } ;

/* Variables and functions */
 scalar_t__ INB (struct ipmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTB (struct ipmi_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SMIC_CTL_STS ; 
 int /*<<< orphan*/  SMIC_DATA ; 
 scalar_t__ SMIC_SC_SMS_RD_END ; 
 scalar_t__ SMIC_SC_SMS_RD_NEXT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  smic_set_busy (struct ipmi_softc*) ; 
 int /*<<< orphan*/  smic_wait_for_not_busy (struct ipmi_softc*) ; 
 int /*<<< orphan*/  smic_wait_for_rx_okay (struct ipmi_softc*) ; 

__attribute__((used)) static int
smic_read_byte(struct ipmi_softc *sc, u_char *data)
{
	u_char error, status;

	smic_wait_for_rx_okay(sc);
	OUTB(sc, SMIC_CTL_STS, SMIC_SC_SMS_RD_NEXT);
	smic_set_busy(sc);
	smic_wait_for_not_busy(sc);
	status = INB(sc, SMIC_CTL_STS);
	if (status != SMIC_SC_SMS_RD_NEXT &&
	    status != SMIC_SC_SMS_RD_END) {
		error = INB(sc, SMIC_DATA);
		device_printf(sc->ipmi_dev, "SMIC: Read did not next %02x\n",
		    error);
		return (0);
	}
	*data = INB(sc, SMIC_DATA);
	if (status == SMIC_SC_SMS_RD_NEXT)
		return (1);
	else
		return (2);
}