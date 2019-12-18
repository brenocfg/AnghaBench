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
typedef  int /*<<< orphan*/  uint32_t ;
struct chipc_softc {int /*<<< orphan*/  core; } ;
struct chipc_caps {int /*<<< orphan*/  pmu; } ;
struct bhnd_pmu_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 struct chipc_caps* BHND_CHIPC_GET_CAPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_CAP ; 
 int /*<<< orphan*/  BHND_PMU_CAP_REV ; 
 int /*<<< orphan*/  BHND_PMU_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BUS_PROBE_NOWILDCARD ; 
 int ENXIO ; 
 int /*<<< orphan*/  bhnd_bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bhnd_pmu_probe (int /*<<< orphan*/ ) ; 
 scalar_t__ devclass_find (char*) ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bhnd_pmu_chipc_probe(device_t dev)
{
	struct bhnd_pmu_softc	*sc;
	struct chipc_caps	*ccaps;
	struct chipc_softc	*chipc_sc;
	device_t		 chipc;
	char			 desc[34];
	int			 error;
	uint32_t		 pcaps;
	uint8_t			 rev;

	sc = device_get_softc(dev);

	/* Look for chipc parent */
	chipc = device_get_parent(dev);
	if (device_get_devclass(chipc) != devclass_find("bhnd_chipc"))
		return (ENXIO);

	/* Check the chipc PMU capability flag. */
	ccaps = BHND_CHIPC_GET_CAPS(chipc);
	if (!ccaps->pmu)
		return (ENXIO);

	/* Delegate to common driver implementation */
	if ((error = bhnd_pmu_probe(dev)) > 0)
		return (error);

	/* Fetch PMU capability flags */
	chipc_sc = device_get_softc(chipc);
	pcaps = bhnd_bus_read_4(chipc_sc->core, BHND_PMU_CAP);

	/* Set description */
	rev = BHND_PMU_GET_BITS(pcaps, BHND_PMU_CAP_REV);
	snprintf(desc, sizeof(desc), "Broadcom ChipCommon PMU, rev %hhu", rev);
	device_set_desc_copy(dev, desc);

	return (BUS_PROBE_NOWILDCARD);
}