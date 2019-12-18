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
struct its_cmd {int dummy; } ;
struct gicv3_its_softc {size_t sc_its_cmd_next_idx; struct its_cmd* sc_its_cmd_base; int /*<<< orphan*/  sc_its_cmd_lock; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ITS_CMDQ_SIZE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 struct gicv3_its_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ its_cmd_queue_full (struct gicv3_its_softc*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct its_cmd *
its_cmd_alloc_locked(device_t dev)
{
	struct gicv3_its_softc *sc;
	struct its_cmd *cmd;
	size_t us_left;

	sc = device_get_softc(dev);

	/*
	 * XXX ARM64TODO: This is obviously a significant delay.
	 * The reason for that is that currently the time frames for
	 * the command to complete (and therefore free the descriptor)
	 * are not known.
	 */
	us_left = 1000000;

	mtx_assert(&sc->sc_its_cmd_lock, MA_OWNED);
	while (its_cmd_queue_full(sc)) {
		if (us_left-- == 0) {
			/* Timeout while waiting for free command */
			device_printf(dev,
			    "Timeout while waiting for free command\n");
			return (NULL);
		}
		DELAY(1);
	}

	cmd = &sc->sc_its_cmd_base[sc->sc_its_cmd_next_idx];
	sc->sc_its_cmd_next_idx++;
	sc->sc_its_cmd_next_idx %= ITS_CMDQ_SIZE / sizeof(struct its_cmd);

	return (cmd);
}