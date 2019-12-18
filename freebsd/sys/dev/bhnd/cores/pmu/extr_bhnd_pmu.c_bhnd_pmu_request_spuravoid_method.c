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
struct bhnd_pmu_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_pmu_spuravoid ;

/* Variables and functions */
 int /*<<< orphan*/  BPMU_LOCK (struct bhnd_pmu_softc*) ; 
 int /*<<< orphan*/  BPMU_UNLOCK (struct bhnd_pmu_softc*) ; 
 int bhnd_pmu_set_spuravoid (struct bhnd_pmu_softc*,int /*<<< orphan*/ ) ; 
 struct bhnd_pmu_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_pmu_request_spuravoid_method(device_t dev, bhnd_pmu_spuravoid spuravoid)
{
	struct bhnd_pmu_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);

	BPMU_LOCK(sc);
	error = bhnd_pmu_set_spuravoid(sc, spuravoid);
	BPMU_UNLOCK(sc);

	return (error);
}