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
struct iwn_softc {scalar_t__ eeprom_temp; scalar_t__ eeprom_temp_high; scalar_t__ eeprom_voltage; } ;
struct iwn5000_phy_calib_temp_offsetv2 {int ngroups; int isvalid; void* burnt_voltage_ref; void* offset_high; void* offset_low; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct iwn_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWN5000_PHY_CALIB_TEMP_OFFSET ; 
 int /*<<< orphan*/  IWN_CMD_PHY_CALIB ; 
 int /*<<< orphan*/  IWN_DEBUG_CALIBRATE ; 
 scalar_t__ IWN_DEFAULT_TEMP_OFFSET ; 
 void* htole16 (scalar_t__) ; 
 int iwn_cmd (struct iwn_softc*,int /*<<< orphan*/ ,struct iwn5000_phy_calib_temp_offsetv2*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (void*) ; 
 int /*<<< orphan*/  memset (struct iwn5000_phy_calib_temp_offsetv2*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwn5000_temp_offset_calibv2(struct iwn_softc *sc)
{
	struct iwn5000_phy_calib_temp_offsetv2 cmd;

	memset(&cmd, 0, sizeof cmd);
	cmd.code = IWN5000_PHY_CALIB_TEMP_OFFSET;
	cmd.ngroups = 1;
	cmd.isvalid = 1;
	if (sc->eeprom_temp != 0) {
		cmd.offset_low = htole16(sc->eeprom_temp);
		cmd.offset_high = htole16(sc->eeprom_temp_high);
	} else {
		cmd.offset_low = htole16(IWN_DEFAULT_TEMP_OFFSET);
		cmd.offset_high = htole16(IWN_DEFAULT_TEMP_OFFSET);
	}
	cmd.burnt_voltage_ref = htole16(sc->eeprom_voltage);

	DPRINTF(sc, IWN_DEBUG_CALIBRATE,
	    "setting radio sensor low offset to %d, high offset to %d, voltage to %d\n",
	    le16toh(cmd.offset_low),
	    le16toh(cmd.offset_high),
	    le16toh(cmd.burnt_voltage_ref));

	return iwn_cmd(sc, IWN_CMD_PHY_CALIB, &cmd, sizeof cmd, 0);
}