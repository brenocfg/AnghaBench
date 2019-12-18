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
struct wb_softc {unsigned int timeout_override; int reg_timeout; int reg_1; int reg_2; scalar_t__ debug_verbose; int /*<<< orphan*/  time_reg; int /*<<< orphan*/  dev; int /*<<< orphan*/  ctl_reg; int /*<<< orphan*/  csr_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int WB_LDN8_CRF5_SCALE ; 
 int WB_LDN8_CRF7_TS ; 
 void* superio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wb_print_state (struct wb_softc*,char*) ; 

__attribute__((used)) static int
wb_set_watchdog(struct wb_softc *sc, unsigned int timeout)
{

	if (timeout != 0) {
		/*
		 * In case an override is set, let it override.  It may lead
		 * to strange results as we do not check the input of the sysctl.
		 */
		if (sc->timeout_override > 0)
			timeout = sc->timeout_override;

		/* Make sure we support the requested timeout. */
		if (timeout > 255 * 60)
			return (EINVAL);
	}

	if (sc->debug_verbose)
		wb_print_state(sc, "Before watchdog counter (re)load");

	if (timeout == 0) {
		/* Disable watchdog. */
		sc->reg_timeout = 0;
		superio_write(sc->dev, sc->time_reg, sc->reg_timeout);

	} else {
		/* Read current scaling factor. */
		sc->reg_1 = superio_read(sc->dev, sc->ctl_reg);

		if (timeout > 255) {
			/* Set scaling factor to 60s. */
			sc->reg_1 |= WB_LDN8_CRF5_SCALE;
			sc->reg_timeout = (timeout / 60);
			if (timeout % 60)
				sc->reg_timeout++;
		} else {
			/* Set scaling factor to 1s. */
			sc->reg_1 &= ~WB_LDN8_CRF5_SCALE;
			sc->reg_timeout = timeout;
		}

		/* In case we fired before we need to clear to fire again. */
		sc->reg_2 = superio_read(sc->dev, sc->csr_reg);
		if (sc->reg_2 & WB_LDN8_CRF7_TS) {
			sc->reg_2 &= ~WB_LDN8_CRF7_TS;
			superio_write(sc->dev, sc->csr_reg, sc->reg_2);
		}

		/* Write back scaling factor. */
		superio_write(sc->dev, sc->ctl_reg, sc->reg_1);

		/* Set timer and arm/reset the watchdog. */
		superio_write(sc->dev, sc->time_reg, sc->reg_timeout);
	}

	if (sc->debug_verbose)
		wb_print_state(sc, "After watchdog counter (re)load");
	return (0);
}