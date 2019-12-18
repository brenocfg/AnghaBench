#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {int chip_id; } ;
struct bhnd_pmu_softc {int /*<<< orphan*/  chipc_dev; int /*<<< orphan*/  caps; TYPE_1__ cid; } ;
struct TYPE_6__ {scalar_t__ resnum; scalar_t__ updown; } ;
typedef  TYPE_2__ pmu_res_updown_t ;
typedef  int /*<<< orphan*/  (* pmu_res_filter ) (struct bhnd_pmu_softc*) ;
struct TYPE_7__ {int res_mask; int action; scalar_t__ depend_mask; int /*<<< orphan*/  (* filter ) (struct bhnd_pmu_softc*) ;} ;
typedef  TYPE_3__ pmu_res_depend_t ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_8__ {int /*<<< orphan*/  depend_mask; } ;

/* Variables and functions */
#define  BHND_CHIPID_BCM4315 137 
#define  BHND_CHIPID_BCM4319 136 
#define  BHND_CHIPID_BCM4325 135 
#define  BHND_CHIPID_BCM4328 134 
#define  BHND_CHIPID_BCM4329 133 
#define  BHND_CHIPID_BCM4330 132 
#define  BHND_CHIPID_BCM4336 131 
 int BHND_PMURES_BIT (scalar_t__) ; 
 int /*<<< orphan*/  BHND_PMU_CAP_RC ; 
 scalar_t__ BHND_PMU_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_MAX_RES_MASK ; 
 int /*<<< orphan*/  BHND_PMU_MIN_RES_MASK ; 
 scalar_t__ BHND_PMU_READ_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_RES_DEP_MASK ; 
 int /*<<< orphan*/  BHND_PMU_RES_TABLE_SEL ; 
 int /*<<< orphan*/  BHND_PMU_RES_UPDN_TIMER ; 
 int /*<<< orphan*/  BHND_PMU_WRITE_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PMU_DEBUG (struct bhnd_pmu_softc*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  PMU_LOG (struct bhnd_pmu_softc*,char*,char*,int) ; 
#define  RES_DEPEND_ADD 130 
#define  RES_DEPEND_REMOVE 129 
#define  RES_DEPEND_SET 128 
 void* bcm4315a0_res_depend ; 
 void* bcm4315a0_res_updown ; 
 void* bcm4319a0_res_depend ; 
 void* bcm4319a0_res_updown ; 
 void* bcm4325a0_res_depend ; 
 void* bcm4325a0_res_updown ; 
 void* bcm4328a0_res_depend ; 
 void* bcm4328a0_res_updown ; 
 void* bcm4329_res_depend ; 
 void* bcm4329_res_updown ; 
 void* bcm4330a0_res_depend ; 
 void* bcm4330a0_res_updown ; 
 void* bcm4336a0_res_depend ; 
 void* bcm4336a0_res_updown ; 
 int bhnd_nvram_getvar_uint32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int bhnd_pmu_res_masks (struct bhnd_pmu_softc*,scalar_t__*,scalar_t__*) ; 
 size_t nitems (void*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 TYPE_4__* table ; 

int
bhnd_pmu_res_init(struct bhnd_pmu_softc *sc)
{
	const pmu_res_updown_t		*pmu_res_updown_table;
	const pmu_res_depend_t		*pmu_res_depend_table;
	size_t				 pmu_res_updown_table_sz;
	size_t				 pmu_res_depend_table_sz;
	uint32_t			 max_mask, min_mask;
	uint8_t				 rsrcs;
	int				 error;

	pmu_res_depend_table = NULL;
	pmu_res_depend_table_sz = 0;

	pmu_res_updown_table = NULL;
	pmu_res_updown_table_sz = 0;

	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4315:
		/* Optimize resources up/down timers */
		pmu_res_updown_table = bcm4315a0_res_updown;
		pmu_res_updown_table_sz = nitems(bcm4315a0_res_updown);

		/* Optimize resources dependencies */
		pmu_res_depend_table = bcm4315a0_res_depend;
		pmu_res_depend_table_sz = nitems(bcm4315a0_res_depend);
		break;

	case BHND_CHIPID_BCM4325:
		/* Optimize resources up/down timers */
		pmu_res_updown_table = bcm4325a0_res_updown;
		pmu_res_updown_table_sz = nitems(bcm4325a0_res_updown);

		/* Optimize resources dependencies */
		pmu_res_depend_table = bcm4325a0_res_depend;
		pmu_res_depend_table_sz = nitems(bcm4325a0_res_depend);
		break;

	case BHND_CHIPID_BCM4328:
		/* Optimize resources up/down timers */
		pmu_res_updown_table = bcm4328a0_res_updown;
		pmu_res_updown_table_sz = nitems(bcm4328a0_res_updown);

		/* Optimize resources dependencies */
		pmu_res_depend_table = bcm4328a0_res_depend;
		pmu_res_depend_table_sz = nitems(bcm4328a0_res_depend);
		break;

	case BHND_CHIPID_BCM4329:
		/* Optimize resources up/down timers */
		pmu_res_updown_table = bcm4329_res_updown;
		pmu_res_updown_table_sz = nitems(bcm4329_res_updown);

		/* Optimize resources dependencies */
		pmu_res_depend_table = bcm4329_res_depend;
		pmu_res_depend_table_sz = nitems(bcm4329_res_depend);
		break;

	case BHND_CHIPID_BCM4319:
		/* Optimize resources up/down timers */
		pmu_res_updown_table = bcm4319a0_res_updown;
		pmu_res_updown_table_sz = nitems(bcm4319a0_res_updown);
		
		/* Optimize resources dependencies masks */
		pmu_res_depend_table = bcm4319a0_res_depend;
		pmu_res_depend_table_sz = nitems(bcm4319a0_res_depend);
		break;

	case BHND_CHIPID_BCM4336:
		/* Optimize resources up/down timers */
		pmu_res_updown_table = bcm4336a0_res_updown;
		pmu_res_updown_table_sz = nitems(bcm4336a0_res_updown);

		/* Optimize resources dependencies masks */
		pmu_res_depend_table = bcm4336a0_res_depend;
		pmu_res_depend_table_sz = nitems(bcm4336a0_res_depend);
		break;

	case BHND_CHIPID_BCM4330:
		/* Optimize resources up/down timers */
		pmu_res_updown_table = bcm4330a0_res_updown;
		pmu_res_updown_table_sz = nitems(bcm4330a0_res_updown);

		/* Optimize resources dependencies masks */
		pmu_res_depend_table = bcm4330a0_res_depend;
		pmu_res_depend_table_sz = nitems(bcm4330a0_res_depend);
		break;
	default:
		break;
	}

	/* # resources */
	rsrcs = BHND_PMU_GET_BITS(sc->caps, BHND_PMU_CAP_RC);

	/* Program up/down timers */
	for (size_t i = 0; i < pmu_res_updown_table_sz; i++) {
		const pmu_res_updown_t	*updt;

		KASSERT(pmu_res_updown_table != NULL, ("no updown tables"));

		updt = &pmu_res_updown_table[pmu_res_updown_table_sz - i - 1];
	
		PMU_DEBUG(sc, "Changing rsrc %d res_updn_timer to %#x\n",
		    updt->resnum, updt->updown);

		BHND_PMU_WRITE_4(sc, BHND_PMU_RES_TABLE_SEL, updt->resnum);
		BHND_PMU_WRITE_4(sc, BHND_PMU_RES_UPDN_TIMER, updt->updown);
	}

	/* Apply nvram overrides to up/down timers */
	for (uint8_t i = 0; i < rsrcs; i++) {
		char		name[6];
		uint32_t	val;

		snprintf(name, sizeof(name), "r%dt", i);
		error = bhnd_nvram_getvar_uint32(sc->chipc_dev, name, &val);

		if (error == ENOENT) {
			continue;
		} else if (error) {
			PMU_LOG(sc, "NVRAM error reading %s: %d\n",
			    name, error);
			return (error);
		}

		PMU_DEBUG(sc, "Applying %s=%d to rsrc %d res_updn_timer\n",
		    name, val, i);

		BHND_PMU_WRITE_4(sc, BHND_PMU_RES_TABLE_SEL, i);
		BHND_PMU_WRITE_4(sc, BHND_PMU_RES_UPDN_TIMER, val);
	}

	/* Program resource dependencies table */
	for (size_t i = 0; i < pmu_res_depend_table_sz; i++) {
		const pmu_res_depend_t	*rdep;
		pmu_res_filter		 filter;
		uint32_t		 depend_mask;

		KASSERT(pmu_res_depend_table != NULL, ("no depend tables"));

		rdep = &pmu_res_depend_table[pmu_res_depend_table_sz - i - 1];
		filter = rdep->filter;

		if (filter != NULL && !filter(sc))
			continue;

		for (uint8_t i = 0; i < rsrcs; i++) {
			if ((rdep->res_mask & BHND_PMURES_BIT(i)) == 0)
				continue;

			BHND_PMU_WRITE_4(sc, BHND_PMU_RES_TABLE_SEL, i);
			depend_mask = BHND_PMU_READ_4(sc,
			    BHND_PMU_RES_DEP_MASK);
			switch (rdep->action) {
			case RES_DEPEND_SET:
				PMU_DEBUG(sc, "Changing rsrc %hhu res_dep_mask to "
				    "%#x\n", i, table->depend_mask);
				depend_mask = rdep->depend_mask;
				break;

			case RES_DEPEND_ADD:
				PMU_DEBUG(sc, "Adding %#x to rsrc %hhu "
				    "res_dep_mask\n", table->depend_mask, i);

				depend_mask |= rdep->depend_mask;
				break;

			case RES_DEPEND_REMOVE:
				PMU_DEBUG(sc, "Removing %#x from rsrc %hhu "
				    "res_dep_mask\n", table->depend_mask, i);

				depend_mask &= ~(rdep->depend_mask);
				break;

			default:
				panic("unknown RES_DEPEND action: %d\n",
				    rdep->action);
				break;
			}
			
			
		}
	}

	/* Apply nvram overrides to dependencies masks */
	for (uint8_t i = 0; i < rsrcs; i++) {
		char		name[6];
		uint32_t	val;

		snprintf(name, sizeof(name), "r%dd", i);
		error = bhnd_nvram_getvar_uint32(sc->chipc_dev, name, &val);

		if (error == ENOENT) {
			continue;
		} else if (error) {
			PMU_LOG(sc, "NVRAM error reading %s: %d\n", name,
			    error);
			return (error);
		}

		PMU_DEBUG(sc, "Applying %s=%d to rsrc %d res_dep_mask\n", name,
		    val, i);

		BHND_PMU_WRITE_4(sc, BHND_PMU_RES_TABLE_SEL, i);
		BHND_PMU_WRITE_4(sc, BHND_PMU_RES_DEP_MASK, val);
	}

	/* Determine min/max rsrc masks */
	if ((error = bhnd_pmu_res_masks(sc, &min_mask, &max_mask)))
		return (error);

	/* It is required to program max_mask first and then min_mask */

	/* Program max resource mask */
	if (max_mask != 0) {
		PMU_DEBUG(sc, "Changing max_res_mask to 0x%x\n", max_mask);
		BHND_PMU_WRITE_4(sc, BHND_PMU_MAX_RES_MASK, max_mask);
	}

	/* Program min resource mask */

	if (min_mask != 0) {
		PMU_DEBUG(sc, "Changing min_res_mask to 0x%x\n", min_mask);
		BHND_PMU_WRITE_4(sc, BHND_PMU_MIN_RES_MASK, min_mask);
	}

	/* Add some delay; allow resources to come up and settle. */
	DELAY(2000);

	return (0);
}