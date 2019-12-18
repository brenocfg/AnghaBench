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
struct imx6_anatop_softc {int temp_room_cnt; int temp_high_cnt; int temp_high_val; int temp_throttle_val; int temp_throttle_trigger_cnt; scalar_t__ temp_last_cnt; int temp_throttle_delay; int /*<<< orphan*/  temp_throttle_callout; void* temp_throttle_reset_cnt; } ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  FSL_OCOTP_ANA1 ; 
 int /*<<< orphan*/  IMX6_ANALOG_TEMPMON_TEMPSENSE0 ; 
 int IMX6_ANALOG_TEMPMON_TEMPSENSE0_ALARM_SHIFT ; 
 int IMX6_ANALOG_TEMPMON_TEMPSENSE0_MEASURE ; 
 int /*<<< orphan*/  IMX6_ANALOG_TEMPMON_TEMPSENSE1 ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct imx6_anatop_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hw_imx ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct imx6_anatop_softc*,int /*<<< orphan*/ ) ; 
 int fsl_ocotp_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx6_anatop_write_4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  temp_sysctl_handler ; 
 int /*<<< orphan*/  temp_throttle_sysctl_handler ; 
 void* temp_to_count (struct imx6_anatop_softc*,int) ; 
 int /*<<< orphan*/  temp_update_count (struct imx6_anatop_softc*) ; 
 int /*<<< orphan*/  tempmon_throttle_check ; 

__attribute__((used)) static void
initialize_tempmon(struct imx6_anatop_softc *sc)
{
	uint32_t cal;

	/*
	 * Fetch calibration data: a sensor count at room temperature (25C),
	 * a sensor count at a high temperature, and that temperature
	 */
	cal = fsl_ocotp_read_4(FSL_OCOTP_ANA1);
	sc->temp_room_cnt = (cal & 0xFFF00000) >> 20;
	sc->temp_high_cnt = (cal & 0x000FFF00) >> 8;
	sc->temp_high_val = (cal & 0x000000FF) * 10;

	/*
	 * Throttle to a lower cpu freq at 10C below the "hot" temperature, and
	 * reset back to max cpu freq at 5C below the trigger.
	 */
	sc->temp_throttle_val = sc->temp_high_val - 100;
	sc->temp_throttle_trigger_cnt =
	    temp_to_count(sc, sc->temp_throttle_val);
	sc->temp_throttle_reset_cnt = 
	    temp_to_count(sc, sc->temp_throttle_val - 50);

	/*
	 * Set the sensor to sample automatically at 16Hz (32.768KHz/0x800), set
	 * the throttle count, and begin making measurements.
	 */
	imx6_anatop_write_4(IMX6_ANALOG_TEMPMON_TEMPSENSE1, 0x0800);
	imx6_anatop_write_4(IMX6_ANALOG_TEMPMON_TEMPSENSE0,
	    (sc->temp_throttle_trigger_cnt << 
	    IMX6_ANALOG_TEMPMON_TEMPSENSE0_ALARM_SHIFT) |
	    IMX6_ANALOG_TEMPMON_TEMPSENSE0_MEASURE);

	/*
	 * XXX Note that the alarm-interrupt feature isn't working yet, so
	 * we'll use a callout handler to check at 10Hz.  Make sure we have an
	 * initial temperature reading before starting up the callouts so we
	 * don't get a bogus reading of zero.
	 */
	while (sc->temp_last_cnt == 0)
		temp_update_count(sc);
	sc->temp_throttle_delay = 100 * SBT_1MS;
	callout_init(&sc->temp_throttle_callout, 0);
	callout_reset_sbt(&sc->temp_throttle_callout, sc->temp_throttle_delay, 
	    0, tempmon_throttle_check, sc, 0);

	SYSCTL_ADD_PROC(NULL, SYSCTL_STATIC_CHILDREN(_hw_imx), 
	    OID_AUTO, "temperature", CTLTYPE_INT | CTLFLAG_RD, sc, 0,
	    temp_sysctl_handler, "IK", "Current die temperature");
	SYSCTL_ADD_PROC(NULL, SYSCTL_STATIC_CHILDREN(_hw_imx), 
	    OID_AUTO, "throttle_temperature", CTLTYPE_INT | CTLFLAG_RW, sc,
	    0, temp_throttle_sysctl_handler, "IK", 
	    "Throttle CPU when exceeding this temperature");
}