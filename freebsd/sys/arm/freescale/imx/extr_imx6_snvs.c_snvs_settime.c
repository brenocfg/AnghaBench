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
typedef  int /*<<< orphan*/  uint32_t ;
struct timespec {int dummy; } ;
struct snvs_softc {int /*<<< orphan*/  dev; } ;
typedef  int sbintime_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DBG_WRITE ; 
 int SBT_LSB ; 
 int /*<<< orphan*/  SNVS_LPSRTCLR ; 
 int /*<<< orphan*/  SNVS_LPSRTCMR ; 
 int /*<<< orphan*/  WR4 (struct snvs_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_dbgprint_ts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*) ; 
 struct snvs_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snvs_rtc_enable (struct snvs_softc*,int) ; 
 int tstosbt (struct timespec) ; 

__attribute__((used)) static int
snvs_settime(device_t dev, struct timespec *ts)
{
	struct snvs_softc *sc;
	sbintime_t sbt;

	sc = device_get_softc(dev);

	/*
	 * The hardware format is the same as sbt (with fewer fractional bits),
	 * so first convert the time to sbt.  It takes two clock cycles for the
	 * counter to start after setting the enable bit, so add two SBT_LSBs to
	 * what we're about to set.
	 */
	sbt = tstosbt(*ts);
	sbt += 2 << SBT_LSB;
	snvs_rtc_enable(sc, false);
	WR4(sc, SNVS_LPSRTCMR, (uint32_t)(sbt >> (SBT_LSB + 32)));
	WR4(sc, SNVS_LPSRTCLR, (uint32_t)(sbt >> (SBT_LSB)));
	snvs_rtc_enable(sc, true);

	clock_dbgprint_ts(sc->dev, CLOCK_DBG_WRITE, ts); 

	return (0);
}