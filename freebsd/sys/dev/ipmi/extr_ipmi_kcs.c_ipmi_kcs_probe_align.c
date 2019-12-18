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
struct ipmi_softc {int ipmi_io_spacing; int /*<<< orphan*/  ipmi_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int INB (struct ipmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCS_CONTROL_GET_STATUS_ABORT ; 
 int /*<<< orphan*/  KCS_CTL_STS ; 
 int /*<<< orphan*/  KCS_DATA ; 
 int /*<<< orphan*/  KCS_DATA_IN_READ ; 
 int KCS_STATUS_IBF ; 
 int KCS_STATUS_OBF ; 
 int KCS_STATUS_STATE (int) ; 
 int KCS_STATUS_STATE_IDLE ; 
 int KCS_STATUS_STATE_READ ; 
 int /*<<< orphan*/  OUTB (struct ipmi_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
ipmi_kcs_probe_align(struct ipmi_softc *sc)
{
	int data, status;

	sc->ipmi_io_spacing = 1;
retry:
#ifdef KCS_DEBUG
	device_printf(sc->ipmi_dev, "Trying KCS align %d... ", sc->ipmi_io_spacing);
#endif

	/* Wait for IBF = 0 */
	status = INB(sc, KCS_CTL_STS);
	while (status & KCS_STATUS_IBF) {
		DELAY(100);
		status = INB(sc, KCS_CTL_STS);
	}

	OUTB(sc, KCS_CTL_STS, KCS_CONTROL_GET_STATUS_ABORT);

	/* Wait for IBF = 0 */
	status = INB(sc, KCS_CTL_STS);
	while (status & KCS_STATUS_IBF) {
		DELAY(100);
		status = INB(sc, KCS_CTL_STS);
	}

	/* If we got 0x00 back, then this must not be the CTL_STS register. */
	if (status == 0) {
#ifdef KCS_DEBUG
		printf("failed\n");
#endif
		sc->ipmi_io_spacing <<= 1;
		if (sc->ipmi_io_spacing > 4)
			return (0);
		goto retry;
	}
#ifdef KCS_DEBUG
	printf("ok\n");
#endif

	/* Finish out the transaction. */

	/* Clear OBF */
	if (status & KCS_STATUS_OBF)
		data = INB(sc, KCS_DATA);

	/* 0x00 to DATA_IN */
	OUTB(sc, KCS_DATA, 0);

	/* Wait for IBF = 0 */
	status = INB(sc, KCS_CTL_STS);
	while (status & KCS_STATUS_IBF) {
		DELAY(100);
		status = INB(sc, KCS_CTL_STS);
	}

	if (KCS_STATUS_STATE(status) == KCS_STATUS_STATE_READ) {
		/* Wait for IBF = 1 */
		while (!(status & KCS_STATUS_OBF)) {
			DELAY(100);
			status = INB(sc, KCS_CTL_STS);
		}

		/* Read error status. */
		data = INB(sc, KCS_DATA);

		/* Write dummy READ to DATA_IN. */
		OUTB(sc, KCS_DATA, KCS_DATA_IN_READ);

		/* Wait for IBF = 0 */
		status = INB(sc, KCS_CTL_STS);
		while (status & KCS_STATUS_IBF) {
			DELAY(100);
			status = INB(sc, KCS_CTL_STS);
		}
	}

	if (KCS_STATUS_STATE(status) == KCS_STATUS_STATE_IDLE) {
		/* Wait for IBF = 1 */
		while (!(status & KCS_STATUS_OBF)) {
			DELAY(100);
			status = INB(sc, KCS_CTL_STS);
		}

		/* Clear OBF */
		if (status & KCS_STATUS_OBF)
			data = INB(sc, KCS_DATA);
	} else
		device_printf(sc->ipmi_dev, "KCS probe: end state %x\n",
		    KCS_STATUS_STATE(status));

	return (1);
}