#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct csr   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct nxprtc_softc {int use_ampm; int /*<<< orphan*/  dev; scalar_t__ freqadj; scalar_t__ is212x; } ;
typedef  scalar_t__ int8_t ;
typedef  int /*<<< orphan*/  csr ;
struct csr {int cs1; int cs2; int cs3; int sec; } ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RWTUN ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int PCF2127_B_TSOFF ; 
 int /*<<< orphan*/  PCF2127_R_AGING_OFFSET ; 
 int /*<<< orphan*/  PCF2127_R_TS_CTL ; 
 int PCF2129_B_CLKOUT_HIGHZ ; 
 int PCF2129_B_CLKOUT_OTPR ; 
 int PCF2129_B_CS1_12HR ; 
 int PCF8523_B_CLKOUT_HIGHZ ; 
 int PCF8523_B_CS1_12HR ; 
 int PCF8523_B_CS3_PM_NOBAT ; 
 int PCF8523_M_CS3_PM ; 
 int /*<<< orphan*/  PCF8523_R_TMR_CLKOUT ; 
 int PCF85xx_B_CS1_STOP ; 
 int PCF85xx_B_SECOND_OS ; 
 int /*<<< orphan*/  PCF85xx_R_CS1 ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,struct nxprtc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WAITFLAGS ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freqadj_sysctl ; 
 int /*<<< orphan*/  mstosbt (int) ; 
 int nxprtc_readfrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause_sbt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcf8523_battery_check (struct nxprtc_softc*) ; 
 int read_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int*) ; 
 int write_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pcf8523_start(struct nxprtc_softc *sc)
{
	struct sysctl_ctx_list *ctx;
	struct sysctl_oid_list *tree;
	struct csr {
		uint8_t	cs1;
		uint8_t	cs2;
		uint8_t cs3;
		uint8_t sec;
	} csr;
	int err;
	uint8_t clkout, freqadj;

	/* Read the control and status registers. */
	if ((err = nxprtc_readfrom(sc->dev, PCF85xx_R_CS1, &csr,
	    sizeof(csr), WAITFLAGS)) != 0){
		device_printf(sc->dev, "cannot read RTC control regs\n");
		return (err);
	}

	/*
	 * Do a full init if...
	 *  - The chip power manager is in battery-disable mode.
	 *  - The OS (oscillator stopped) bit is set (all power was lost).
	 *  - The clock-increment STOP flag is set (this is just insane).
	 */
	if ((csr.cs3 & PCF8523_M_CS3_PM) == PCF8523_B_CS3_PM_NOBAT ||
	    (csr.cs1 & PCF85xx_B_CS1_STOP) || (csr.sec & PCF85xx_B_SECOND_OS)) {
		device_printf(sc->dev, 
		    "WARNING: RTC battery failed; time is invalid\n");

		/*
		 * For 212x series...
		 * - Turn off the POR-Override bit (used for mfg test only), 
		 *   by writing zero to cs 1 (all other bits power on as zero). 
		 * - Turn off the timestamp option to save the power used to
		 *   monitor that input pin.
		 * - Trigger OTP refresh by forcing the OTPR bit to zero then
		 *   back to 1, then wait 100ms for the refresh.
		 */
		if (sc->is212x) {
			err = write_reg(sc, PCF85xx_R_CS1, 0);
			if (err != 0) {
				device_printf(sc->dev,
				    "cannot write CS1 reg\n");
				return (err);
			}

			err = write_reg(sc, PCF2127_R_TS_CTL, PCF2127_B_TSOFF);
			if (err != 0) {
				device_printf(sc->dev,
				    "cannot write timestamp control\n");
				return (err);
			}

			clkout = PCF2129_B_CLKOUT_HIGHZ;
			err = write_reg(sc, PCF8523_R_TMR_CLKOUT, clkout);
			if (err == 0)
				err = write_reg(sc, PCF8523_R_TMR_CLKOUT,
				    clkout | PCF2129_B_CLKOUT_OTPR);
			if (err != 0) {
				device_printf(sc->dev,
				    "cannot write CLKOUT control\n");
				return (err);
			}
			pause_sbt("nxpotp", mstosbt(100), mstosbt(10), 0);
		} else
			clkout = PCF8523_B_CLKOUT_HIGHZ;

		/* All chips: set clock output pin to high-z to save power */
		if ((err = write_reg(sc, PCF8523_R_TMR_CLKOUT, clkout)) != 0) {
			device_printf(sc->dev, "cannot write CLKOUT control\n");
			return (err);
		}
	}

	/*
	 * Check the battery voltage and report if it's low.  This also has the
	 * side effect of (re-)initializing the power manager to low-power mode
	 * when we come up after a power fail.
	 */
	pcf8523_battery_check(sc);

	/*
	 * Remember whether we're running in AM/PM mode.  The chip default is
	 * 24-hour mode, but if we're co-existing with some other OS that
	 * prefers AM/PM we can run that way too.
	 *
	 * Also, for 212x chips, retrieve the current frequency aging offset,
	 * and set up the sysctl handler for reading/setting it.
	 */
	if (sc->is212x) {
		if (csr.cs1 & PCF2129_B_CS1_12HR)
			sc->use_ampm = true;

		err = read_reg(sc, PCF2127_R_AGING_OFFSET, &freqadj);
		if (err != 0) {
			device_printf(sc->dev,
			    "cannot read AGINGOFFSET register\n");
			return (err);
		}
		sc->freqadj = (int8_t)freqadj;

		ctx = device_get_sysctl_ctx(sc->dev);
		tree = SYSCTL_CHILDREN(device_get_sysctl_tree(sc->dev));

		SYSCTL_ADD_PROC(ctx, tree, OID_AUTO, "freqadj",
		    CTLFLAG_RWTUN | CTLTYPE_INT | CTLFLAG_MPSAFE, sc, 0,
		    freqadj_sysctl, "I", "Frequency adjust in PPM, range [-7,+8]");
	} else {
		if (csr.cs1 & PCF8523_B_CS1_12HR)
			sc->use_ampm = true;
	}

	return (0);
}