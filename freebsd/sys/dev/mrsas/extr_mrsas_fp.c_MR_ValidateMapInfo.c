#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  unsigned int u_int32_t ;
struct mrsas_softc {int map_id; int /*<<< orphan*/  load_balance_info; scalar_t__ UnevenSpanSupport; int /*<<< orphan*/  mrsas_dev; scalar_t__ max256vdSupport; scalar_t__ maxRaidMapSize; int /*<<< orphan*/  log_to_span; TYPE_1__** ld_drv_map; } ;
struct TYPE_6__ {int ldCount; unsigned int totalSize; } ;
struct TYPE_5__ {TYPE_2__ raidMap; } ;
typedef  int /*<<< orphan*/  PLD_SPAN_INFO ;
typedef  int /*<<< orphan*/  MR_LD_SPAN_MAP ;
typedef  int /*<<< orphan*/  MR_FW_RAID_MAP_EXT ;
typedef  int /*<<< orphan*/  MR_FW_RAID_MAP ;
typedef  TYPE_1__ MR_DRV_RAID_MAP_ALL ;
typedef  TYPE_2__ MR_DRV_RAID_MAP ;

/* Variables and functions */
 scalar_t__ MR_PopulateDrvRaidMap (struct mrsas_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  mr_update_span_set (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrsas_update_load_balance_params (struct mrsas_softc*,TYPE_1__*,int /*<<< orphan*/ ) ; 

u_int8_t
MR_ValidateMapInfo(struct mrsas_softc *sc)
{
	if (!sc) {
		return 1;
	}
	if (MR_PopulateDrvRaidMap(sc))
		return 0;

	MR_DRV_RAID_MAP_ALL *drv_map = sc->ld_drv_map[(sc->map_id & 1)];
	MR_DRV_RAID_MAP *pDrvRaidMap = &drv_map->raidMap;

	u_int32_t expected_map_size;

	drv_map = sc->ld_drv_map[(sc->map_id & 1)];
	pDrvRaidMap = &drv_map->raidMap;
	PLD_SPAN_INFO ldSpanInfo = (PLD_SPAN_INFO) & sc->log_to_span;

	if (sc->maxRaidMapSize)
		expected_map_size = sizeof(MR_DRV_RAID_MAP_ALL);
	else if (sc->max256vdSupport)
		expected_map_size = sizeof(MR_FW_RAID_MAP_EXT);
	else
		expected_map_size =
		    (sizeof(MR_FW_RAID_MAP) - sizeof(MR_LD_SPAN_MAP)) +
		    (sizeof(MR_LD_SPAN_MAP) * pDrvRaidMap->ldCount);

	if (pDrvRaidMap->totalSize != expected_map_size) {
		device_printf(sc->mrsas_dev, "map size %x not matching ld count\n", expected_map_size);
		device_printf(sc->mrsas_dev, "span map= %x\n", (unsigned int)sizeof(MR_LD_SPAN_MAP));
		device_printf(sc->mrsas_dev, "pDrvRaidMap->totalSize=%x\n", pDrvRaidMap->totalSize);
		return 1;
	}
	if (sc->UnevenSpanSupport) {
		mr_update_span_set(drv_map, ldSpanInfo);
	}
	mrsas_update_load_balance_params(sc, drv_map, sc->load_balance_info);

	return 0;
}