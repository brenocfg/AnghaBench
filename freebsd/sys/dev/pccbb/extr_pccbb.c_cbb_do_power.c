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
struct cbb_softc {int /*<<< orphan*/ * exca; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CARD_3V_CARD ; 
 int CARD_5V_CARD ; 
 int /*<<< orphan*/  CARD_OFF ; 
 int /*<<< orphan*/  CARD_VCC (int) ; 
 int CARD_XV_CARD ; 
 int CARD_YV_CARD ; 
 int /*<<< orphan*/  CBB_SOCKET_STATE ; 
 int CBB_STATE_POWER_CYCLE ; 
 int ENXIO ; 
 int /*<<< orphan*/  EXCA_PWRCTL ; 
 int /*<<< orphan*/  EXCA_PWRCTL_OE ; 
 int XV ; 
 int YV ; 
 int cbb_current_voltage (int /*<<< orphan*/ ) ; 
 int cbb_detect_voltage (int /*<<< orphan*/ ) ; 
 int cbb_get (struct cbb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cbb_power (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exca_clrb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cbb_do_power(device_t brdev)
{
	struct cbb_softc *sc = device_get_softc(brdev);
	uint32_t voltage, curpwr;
	uint32_t status;

	/* Don't enable OE (output enable) until power stable */
	exca_clrb(&sc->exca[0], EXCA_PWRCTL, EXCA_PWRCTL_OE);

	voltage = cbb_detect_voltage(brdev);
	curpwr = cbb_current_voltage(brdev);
	status = cbb_get(sc, CBB_SOCKET_STATE);
	if ((status & CBB_STATE_POWER_CYCLE) && (voltage & curpwr))
		return 0;
	/* Prefer lowest voltage supported */
	cbb_power(brdev, CARD_OFF);
	if (voltage & CARD_YV_CARD)
		cbb_power(brdev, CARD_VCC(YV));
	else if (voltage & CARD_XV_CARD)
		cbb_power(brdev, CARD_VCC(XV));
	else if (voltage & CARD_3V_CARD)
		cbb_power(brdev, CARD_VCC(3));
	else if (voltage & CARD_5V_CARD)
		cbb_power(brdev, CARD_VCC(5));
	else {
		device_printf(brdev, "Unknown card voltage\n");
		return (ENXIO);
	}
	return (0);
}