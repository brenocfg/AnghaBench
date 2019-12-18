#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int u_int ;
struct aw_wdog_softc {int wdog_mode_intvl_shift; int wdog_mode_en; int wdog_ctrl_key; int wdog_config_value; int /*<<< orphan*/  mtx; scalar_t__ wdog_mode; int /*<<< orphan*/  dev; scalar_t__ wdog_config; scalar_t__ wdog_ctrl; } ;
struct TYPE_2__ {int milliseconds; int value; } ;

/* Variables and functions */
 int WDOG_CTRL_RESTART ; 
 int WD_INTERVAL ; 
 int /*<<< orphan*/  WRITE (struct aw_wdog_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* wd_intervals ; 

__attribute__((used)) static void
aw_wdog_watchdog_fn(void *private, u_int cmd, int *error)
{
	struct aw_wdog_softc *sc;
	uint64_t ms;
	int i;

	sc = private;
	mtx_lock(&sc->mtx);

	cmd &= WD_INTERVAL;

	if (cmd > 0) {
		ms = ((uint64_t)1 << (cmd & WD_INTERVAL)) / 1000000;
		i = 0;
		while (wd_intervals[i].milliseconds &&
		    (ms > wd_intervals[i].milliseconds))
			i++;
		if (wd_intervals[i].milliseconds) {
			WRITE(sc, sc->wdog_mode,
			  (wd_intervals[i].value << sc->wdog_mode_intvl_shift) |
			    sc->wdog_mode_en);
			WRITE(sc, sc->wdog_ctrl,
			    WDOG_CTRL_RESTART | sc->wdog_ctrl_key);
			if (sc->wdog_config)
				WRITE(sc, sc->wdog_config,
				    sc->wdog_config_value);
			*error = 0;
		}
		else {
			/*
			 * Can't arm
			 * disable watchdog as watchdog(9) requires
			 */
			device_printf(sc->dev,
			    "Can't arm, timeout is more than 16 sec\n");
			mtx_unlock(&sc->mtx);
			WRITE(sc, sc->wdog_mode, 0);
			return;
		}
	}
	else
		WRITE(sc, sc->wdog_mode, 0);

	mtx_unlock(&sc->mtx);
}