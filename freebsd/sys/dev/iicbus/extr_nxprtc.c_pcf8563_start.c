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
struct nxprtc_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  csr ;
struct csr {int cs1; int cs2; int sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCF8563_R_CLKOUT ; 
 int PCF85xx_B_CS1_STOP ; 
 int PCF85xx_B_SECOND_OS ; 
 int /*<<< orphan*/  PCF85xx_R_CS1 ; 
 int /*<<< orphan*/  WAITFLAGS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int nxprtc_readfrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int write_reg (struct nxprtc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcf8563_start(struct nxprtc_softc *sc)
{
	struct csr {
		uint8_t	cs1;
		uint8_t	cs2;
		uint8_t sec;
	} csr;
	int err;

	/* Read the control and status registers. */
	if ((err = nxprtc_readfrom(sc->dev, PCF85xx_R_CS1, &csr,
	    sizeof(csr), WAITFLAGS)) != 0){
		device_printf(sc->dev, "cannot read RTC control regs\n");
		return (err);
	}

	/*
	 * Do a full init if...
	 *  - The OS (oscillator stopped) bit is set (all power was lost).  This
	 *    bit is called VL (Voltage Low) in the 8563 datasheet.
	 *  - The clock-increment STOP flag is set (this is just insane).
	 */
	if ((csr.cs1 & PCF85xx_B_CS1_STOP) || (csr.sec & PCF85xx_B_SECOND_OS)) {
		device_printf(sc->dev, 
		    "WARNING: RTC battery failed; time is invalid\n");
		/*
		 * - Turn off the POR-Override bit (used for mfg test only), by
		 *   writing zero to cs 1 (all other bits power on as zero).
		 * - Turn off the clock output pin (to save battery power), by
		 *   writing zero to the clkout control reg.
		 */
		if ((err = write_reg(sc, PCF85xx_R_CS1, 0)) != 0) {
			device_printf(sc->dev, "cannot write CS1 reg\n");
			return (err);
		}

		if ((err = write_reg(sc, PCF8563_R_CLKOUT, 0)) != 0) {
			device_printf(sc->dev, "cannot write CS1 reg\n");
			return (err);
		}
	}

	return (0);
}