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
struct timespec {int dummy; } ;
struct snvs_softc {int /*<<< orphan*/  dev; } ;
typedef  int sbintime_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_DBG_READ ; 
 int EINVAL ; 
 int LPCR_SRTC_ENV ; 
 int RD4 (struct snvs_softc*,int /*<<< orphan*/ ) ; 
 int SBT_LSB ; 
 int /*<<< orphan*/  SNVS_LPCR ; 
 int /*<<< orphan*/  SNVS_LPSRTCLR ; 
 int /*<<< orphan*/  SNVS_LPSRTCMR ; 
 int /*<<< orphan*/  clock_dbgprint_ts (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*) ; 
 struct snvs_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 struct timespec sbttots (int) ; 

__attribute__((used)) static int
snvs_gettime(device_t dev, struct timespec *ts)
{
	struct snvs_softc *sc;
	sbintime_t counter1, counter2;

	sc = device_get_softc(dev);

	/* If the clock is not enabled and valid, we can't help. */
	if (!(RD4(sc, SNVS_LPCR) & LPCR_SRTC_ENV)) {
		return (EINVAL);
	}

	/*
	 * The counter is clocked asynchronously to cpu accesses; read and
	 * assemble the pieces of the counter until we get the same value twice.
	 * The counter is 47 bits, organized as a 32.15 binary fixed-point
	 * value. If we shift it up to the high order part of a 64-bit word it
	 * turns into an sbintime.
	 */
	do {
		counter1  = (uint64_t)RD4(sc, SNVS_LPSRTCMR) << (SBT_LSB + 32);
		counter1 |= (uint64_t)RD4(sc, SNVS_LPSRTCLR) << (SBT_LSB);
		counter2  = (uint64_t)RD4(sc, SNVS_LPSRTCMR) << (SBT_LSB + 32);
		counter2 |= (uint64_t)RD4(sc, SNVS_LPSRTCLR) << (SBT_LSB);
	} while (counter1 != counter2);

	*ts = sbttots(counter1);

	clock_dbgprint_ts(sc->dev, CLOCK_DBG_READ, ts); 

	return (0);
}