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
typedef  int /*<<< orphan*/  u_char ;
struct ipmi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INB (struct ipmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCS_DATA ; 
 int /*<<< orphan*/  KCS_DATA_IN_READ ; 
 int KCS_STATUS_OBF ; 
 scalar_t__ KCS_STATUS_STATE (int) ; 
 scalar_t__ KCS_STATUS_STATE_IDLE ; 
 scalar_t__ KCS_STATUS_STATE_READ ; 
 int /*<<< orphan*/  OUTB (struct ipmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kcs_wait_for_ibf (struct ipmi_softc*,int /*<<< orphan*/ ) ; 
 int kcs_wait_for_obf (struct ipmi_softc*,int) ; 

__attribute__((used)) static int
kcs_read_byte(struct ipmi_softc *sc, u_char *data)
{
	int status;
	u_char dummy;

	/* Wait for IBF = 0 */
	status = kcs_wait_for_ibf(sc, 0);

	/* Read State */
	if (KCS_STATUS_STATE(status) == KCS_STATUS_STATE_READ) {

		/* Wait for OBF = 1 */
		status = kcs_wait_for_obf(sc, 1);
		if ((status & KCS_STATUS_OBF) == 0)
			return (0);

		/* Read Data_out */
		*data = INB(sc, KCS_DATA);

		/* Write READ into Data_in */
		OUTB(sc, KCS_DATA, KCS_DATA_IN_READ);
		return (1);
	}

	/* Idle State */
	if (KCS_STATUS_STATE(status) == KCS_STATUS_STATE_IDLE) {

		/* Wait for OBF = 1*/
		status = kcs_wait_for_obf(sc, 1);
		if ((status & KCS_STATUS_OBF) == 0)
			return (0);

		/* Read Dummy */
		dummy = INB(sc, KCS_DATA);
		return (2);
	}

	/* Error State */
	return (0);
}