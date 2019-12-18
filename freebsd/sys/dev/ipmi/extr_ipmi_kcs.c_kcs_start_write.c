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
struct ipmi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  KCS_CONTROL_WRITE_START ; 
 int /*<<< orphan*/  KCS_CTL_STS ; 
 int KCS_STATUS_IBF ; 
 scalar_t__ KCS_STATUS_STATE (int) ; 
 scalar_t__ KCS_STATUS_STATE_WRITE ; 
 int /*<<< orphan*/  OUTB (struct ipmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcs_clear_obf (struct ipmi_softc*,int) ; 
 int kcs_wait_for_ibf (struct ipmi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kcs_start_write(struct ipmi_softc *sc)
{
	int retry, status;

	for (retry = 0; retry < 10; retry++) {
		/* Wait for IBF = 0 */
		status = kcs_wait_for_ibf(sc, 0);
		if (status & KCS_STATUS_IBF)
			return (0);

		/* Clear OBF */
		kcs_clear_obf(sc, status);

		/* Write start to command */
		OUTB(sc, KCS_CTL_STS, KCS_CONTROL_WRITE_START);

		/* Wait for IBF = 0 */
		status = kcs_wait_for_ibf(sc, 0);
		if (status & KCS_STATUS_IBF)
			return (0);

		if (KCS_STATUS_STATE(status) == KCS_STATUS_STATE_WRITE)
			break;
		DELAY(1000000);
	}

	if (KCS_STATUS_STATE(status) != KCS_STATUS_STATE_WRITE)
		/* error state */
		return (0);

	/* Clear OBF */
	kcs_clear_obf(sc, status);

	return (1);
}