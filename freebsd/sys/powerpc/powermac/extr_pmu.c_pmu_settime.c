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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct timespec {scalar_t__ tv_sec; } ;
struct pmu_softc {int /*<<< orphan*/  sc_mutex; } ;
typedef  int /*<<< orphan*/  sec ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ DIFF19041970 ; 
 int /*<<< orphan*/  PMU_SET_RTC ; 
 struct pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmu_send (struct pmu_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pmu_settime(device_t dev, struct timespec *ts)
{
	struct pmu_softc *sc = device_get_softc(dev);
	uint32_t sec;

	sec = ts->tv_sec + DIFF19041970;

	mtx_lock(&sc->sc_mutex);
	pmu_send(sc, PMU_SET_RTC, sizeof(sec), (uint8_t *)&sec, 0, NULL);
	mtx_unlock(&sc->sc_mutex);

	return (0);
}