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
typedef  int uint64_t ;
typedef  int u_int ;
struct rk30_wd_softc {int freq; int /*<<< orphan*/  mtx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK30_WDT_WRITE (struct rk30_wd_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WDOG_CRR ; 
 int WDOG_CRR_PWD ; 
 int /*<<< orphan*/  WDOG_CTRL ; 
 int WDOG_CTRL_EN ; 
 int WDOG_CTRL_RSP_MODE ; 
 int WDOG_CTRL_RST ; 
 int WDOG_CTRL_RST_PULSE ; 
 int /*<<< orphan*/  WDOG_TORR ; 
 int WDOG_TORR_INTVL_SHIFT ; 
 int WD_INTERVAL ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rk30_wd_watchdog_fn(void *private, u_int cmd, int *error)
{
	struct rk30_wd_softc *sc;
	uint64_t ms, m, max;
	int i;

	sc = private;
	mtx_lock(&sc->mtx);

	cmd &= WD_INTERVAL;

	if (cmd > 0) {
		ms = ((uint64_t)1 << (cmd & WD_INTERVAL)) / 1000000;
		m = 0xffff / sc->freq;
		max = 0x7fffffff / sc->freq + 1;
		i = 0;
		while (m < max && m < ms) {
			m <<= 1;
			i++;
		}
		if (m < max) {
			RK30_WDT_WRITE(sc, WDOG_TORR,
			    i << WDOG_TORR_INTVL_SHIFT);
			RK30_WDT_WRITE(sc, WDOG_CTRL,
			    WDOG_CTRL_EN | WDOG_CTRL_RSP_MODE |
			    WDOG_CTRL_RST_PULSE);
			RK30_WDT_WRITE(sc, WDOG_CRR, WDOG_CRR_PWD);
			*error = 0;
		} else {
			device_printf(sc->dev, "Can not be disabled\n");
			mtx_unlock(&sc->mtx);
			RK30_WDT_WRITE(sc, WDOG_CTRL, WDOG_CTRL_RST);
			return;
		}
	}
	else
		RK30_WDT_WRITE(sc, WDOG_CTRL, WDOG_CTRL_RST);

	mtx_unlock(&sc->mtx);
}