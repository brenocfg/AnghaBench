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
struct bhnd_pmu_softc {int /*<<< orphan*/  query; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int bhnd_clock ;

/* Variables and functions */
#define  BHND_CLOCK_ALP 131 
#define  BHND_CLOCK_DYN 130 
#define  BHND_CLOCK_HT 129 
#define  BHND_CLOCK_ILP 128 
 int /*<<< orphan*/  BPMU_LOCK (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  BPMU_UNLOCK (struct bhnd_pmu_softc*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  bhnd_pmu_alp_clock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_pmu_ilp_clock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bhnd_pmu_si_clock (int /*<<< orphan*/ *) ; 
 struct bhnd_pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_pmu_get_clock_freq_method(device_t dev, bhnd_clock clock, uint32_t *freq)
{
	struct bhnd_pmu_softc	*sc = device_get_softc(dev);

	BPMU_LOCK(sc);
	switch (clock) {
	case BHND_CLOCK_HT:
		*freq = bhnd_pmu_si_clock(&sc->query);
		break;

	case BHND_CLOCK_ALP:
		*freq = bhnd_pmu_alp_clock(&sc->query);
		break;

	case BHND_CLOCK_ILP:
		*freq = bhnd_pmu_ilp_clock(&sc->query);
		break;

	case BHND_CLOCK_DYN:
	default:
		BPMU_UNLOCK(sc);
		return (ENODEV);
	}

	BPMU_UNLOCK(sc);
	return (0);
}