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
struct tegra_i2c_softc {scalar_t__ done; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  LOCK (struct tegra_i2c_softc*) ; 
 int /*<<< orphan*/  UNLOCK (struct tegra_i2c_softc*) ; 
 int /*<<< orphan*/  tegra_i2c_intr (struct tegra_i2c_softc*) ; 

__attribute__((used)) static int
tegra_i2c_poll(struct tegra_i2c_softc *sc)
{
	int timeout;

	for(timeout = 10000; timeout > 0; timeout--)  {
		UNLOCK(sc);
		tegra_i2c_intr(sc);
		LOCK(sc);
		if (sc->done != 0)
			 break;
		DELAY(1);
	}
	if (timeout <= 0)
		return (ETIMEDOUT);
	return (0);
}