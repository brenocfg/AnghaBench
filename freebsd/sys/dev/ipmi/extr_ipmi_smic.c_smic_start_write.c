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
 scalar_t__ SMIC_CC_SMS_WR_START ; 
 int /*<<< orphan*/  SMIC_CTL_STS ; 
 int /*<<< orphan*/  SMIC_DATA ; 
 scalar_t__ SMIC_SC_SMS_WR_START ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  smic_set_busy (struct ipmi_softc*) ; 
 int /*<<< orphan*/  smic_wait_for_not_busy (struct ipmi_softc*) ; 

__attribute__((used)) static int
smic_start_write(struct ipmi_softc *sc, u_char data)
{
	u_char error, status;

	smic_wait_for_not_busy(sc);

	OUTB(sc, SMIC_CTL_STS, SMIC_CC_SMS_WR_START);
	OUTB(sc, SMIC_DATA, data);
	smic_set_busy(sc);
	smic_wait_for_not_busy(sc);
	status = INB(sc, SMIC_CTL_STS);
	if (status != SMIC_SC_SMS_WR_START) {
		error = INB(sc, SMIC_DATA);
		device_printf(sc->ipmi_dev, "SMIC: Write did not start %02x\n",
		    error);
		return (0);
	}
	return (1);
}