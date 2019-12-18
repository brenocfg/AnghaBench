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
struct iwi_softc {int dummy; } ;
struct iwi_sensitivity {int /*<<< orphan*/  rssi; } ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  IWI_CMD_SET_SENSITIVITY ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 int iwi_cmd (struct iwi_softc*,int /*<<< orphan*/ ,struct iwi_sensitivity*,int) ; 
 int /*<<< orphan*/  memset (struct iwi_sensitivity*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
iwi_set_sensitivity(struct iwi_softc *sc, int8_t rssi_dbm)
{
	struct iwi_sensitivity sens;

	DPRINTF(("Setting sensitivity to %d\n", rssi_dbm));

	memset(&sens, 0, sizeof sens);
	sens.rssi = htole16(rssi_dbm);
	return iwi_cmd(sc, IWI_CMD_SET_SENSITIVITY, &sens, sizeof sens);
}