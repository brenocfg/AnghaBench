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
struct iwn_softc {int /*<<< orphan*/  eeprom_crystal; } ;
struct iwn5000_phy_calib_crystal {int ngroups; int isvalid; int* cap_pin; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct iwn_softc*,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  IWN5000_PHY_CALIB_CRYSTAL ; 
 int /*<<< orphan*/  IWN_CMD_PHY_CALIB ; 
 int /*<<< orphan*/  IWN_DEBUG_CALIBRATE ; 
 int iwn_cmd (struct iwn_softc*,int /*<<< orphan*/ ,struct iwn5000_phy_calib_crystal*,int,int /*<<< orphan*/ ) ; 
 int le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct iwn5000_phy_calib_crystal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwn5000_crystal_calib(struct iwn_softc *sc)
{
	struct iwn5000_phy_calib_crystal cmd;

	memset(&cmd, 0, sizeof cmd);
	cmd.code = IWN5000_PHY_CALIB_CRYSTAL;
	cmd.ngroups = 1;
	cmd.isvalid = 1;
	cmd.cap_pin[0] = le32toh(sc->eeprom_crystal) & 0xff;
	cmd.cap_pin[1] = (le32toh(sc->eeprom_crystal) >> 16) & 0xff;
	DPRINTF(sc, IWN_DEBUG_CALIBRATE, "sending crystal calibration %d, %d\n",
	    cmd.cap_pin[0], cmd.cap_pin[1]);
	return iwn_cmd(sc, IWN_CMD_PHY_CALIB, &cmd, sizeof cmd, 0);
}