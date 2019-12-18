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
struct bhnd_pmu_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PMU_CCTRL_WRITE (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BPMU_LOCK (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  BPMU_UNLOCK (struct bhnd_pmu_softc*) ; 
 struct bhnd_pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bhnd_pmu_write_chipctrl_method(device_t dev, uint32_t reg, uint32_t value,
    uint32_t mask)
{
	struct bhnd_pmu_softc *sc = device_get_softc(dev);

	BPMU_LOCK(sc);
	BHND_PMU_CCTRL_WRITE(sc, reg, value, mask);
	BPMU_UNLOCK(sc);
}