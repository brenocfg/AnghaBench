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
struct iicbb_softc {int scl_low_timeout; scalar_t__ udelay; } ;
typedef  scalar_t__ sbintime_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_PREL (int) ; 
 int /*<<< orphan*/  DELAY (scalar_t__) ; 
 scalar_t__ I2C_GETSCL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I2C_SETSCL (int /*<<< orphan*/ ,int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  SBT_1MS ; 
 int SBT_1US ; 
 struct iicbb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause_sbt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sbinuptime () ; 

__attribute__((used)) static void
iicbb_setscl(device_t dev, int val)
{
	struct iicbb_softc *sc = device_get_softc(dev);
	sbintime_t now, end;
	int fast_timeout;

	I2C_SETSCL(dev, val);
	DELAY(sc->udelay);

	/* Pulling low cannot fail. */
	if (!val)
		return;

	/* Use DELAY for up to 1 ms, then switch to pause. */
	end = sbinuptime() + sc->scl_low_timeout * SBT_1US;
	fast_timeout = MIN(sc->scl_low_timeout, 1000);
	while (fast_timeout > 0) {
		if (I2C_GETSCL(dev))
			return;
		I2C_SETSCL(dev, 1);	/* redundant ? */
		DELAY(sc->udelay);
		fast_timeout -= sc->udelay;
	}

	while (!I2C_GETSCL(dev)) {
		now = sbinuptime();
		if (now >= end)
			break;
		pause_sbt("iicbb-scl-low", SBT_1MS, C_PREL(8), 0);
	}

}