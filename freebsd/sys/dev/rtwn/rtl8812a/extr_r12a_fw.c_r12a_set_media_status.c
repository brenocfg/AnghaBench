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
struct rtwn_softc {int /*<<< orphan*/  sc_dev; } ;
struct r12a_fw_cmd_msrrpt {int macid; scalar_t__ macid_end; int /*<<< orphan*/  msrb0; } ;
typedef  int /*<<< orphan*/  status ;

/* Variables and functions */
 int /*<<< orphan*/  R12A_CMD_MSR_RPT ; 
 int /*<<< orphan*/  R12A_MSRRPT_B0_ASSOC ; 
 int /*<<< orphan*/  R12A_MSRRPT_B0_DISASSOC ; 
 int RTWN_MACID_VALID ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int r88e_fw_cmd (struct rtwn_softc*,int /*<<< orphan*/ ,struct r12a_fw_cmd_msrrpt*,int) ; 

void
r12a_set_media_status(struct rtwn_softc *sc, int macid)
{
	struct r12a_fw_cmd_msrrpt status;
	int error;

	if (macid & RTWN_MACID_VALID)
		status.msrb0 = R12A_MSRRPT_B0_ASSOC;
	else
		status.msrb0 = R12A_MSRRPT_B0_DISASSOC;

	status.macid = (macid & ~RTWN_MACID_VALID);
	status.macid_end = 0;

	error = r88e_fw_cmd(sc, R12A_CMD_MSR_RPT, &status, sizeof(status));
	if (error != 0)
		device_printf(sc->sc_dev, "cannot change media status!\n");
}