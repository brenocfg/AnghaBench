#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  unsigned int u_int8_t ;
typedef  int u_int32_t ;
typedef  unsigned int u_int16_t ;
struct mrsas_softc {int map_id; int /*<<< orphan*/  mrsas_dev; int /*<<< orphan*/  drv_map_sz; scalar_t__* raidmap_mem; scalar_t__ max256vdSupport; scalar_t__ maxRaidMapSize; TYPE_6__** ld_drv_map; } ;
struct TYPE_12__ {int targetId; int seqNum; scalar_t__ rowSize; int /*<<< orphan*/  size; } ;
struct TYPE_19__ {TYPE_1__ ldRaid; } ;
struct TYPE_18__ {unsigned int ldCount; unsigned int* ldTgtIdToLd; int totalSize; TYPE_9__* devHndlInfo; TYPE_9__* arMapInfo; TYPE_9__* ldSpanMap; int /*<<< orphan*/  fpPdIoTimeoutSec; } ;
struct TYPE_17__ {TYPE_7__ raidMap; } ;
struct TYPE_16__ {unsigned int ldCount; int totalSize; TYPE_10__* devHndlInfo; TYPE_10__* arMapInfo; TYPE_9__* ldSpanMap; scalar_t__* ldTgtIdToLd; int /*<<< orphan*/  fpPdIoTimeoutSec; } ;
struct TYPE_15__ {TYPE_5__ raidMap; } ;
struct TYPE_14__ {TYPE_10__* devHndlInfo; TYPE_10__* arMapInfo; TYPE_10__* ldSpanMap; scalar_t__* ldTgtIdToLd; int /*<<< orphan*/  fpPdIoTimeoutSec; scalar_t__ ldCount; } ;
struct TYPE_13__ {int targetId; int seqNum; scalar_t__ rowSize; int /*<<< orphan*/  size; } ;
struct TYPE_11__ {TYPE_2__ ldRaid; } ;
typedef  int /*<<< orphan*/  MR_LD_SPAN_MAP ;
typedef  TYPE_3__ MR_FW_RAID_MAP_EXT ;
typedef  TYPE_4__ MR_FW_RAID_MAP_ALL ;
typedef  TYPE_5__ MR_FW_RAID_MAP ;
typedef  TYPE_6__ MR_DRV_RAID_MAP_ALL ;
typedef  TYPE_7__ MR_DRV_RAID_MAP ;
typedef  int /*<<< orphan*/  MR_DEV_HANDLE_INFO ;
typedef  int /*<<< orphan*/  MR_ARRAY_INFO ;

/* Variables and functions */
 int MAX_API_ARRAYS_EXT ; 
 unsigned int MAX_LOGICAL_DRIVES_EXT ; 
 int MAX_RAIDMAP_ARRAYS ; 
 unsigned int MAX_RAIDMAP_LOGICAL_DRIVES ; 
 int MAX_RAIDMAP_PHYSICAL_DEVICES ; 
 unsigned int MAX_RAIDMAP_VIEWS ; 
 int MR_PopulateDrvRaidMapVentura (struct mrsas_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memcpy (TYPE_9__*,TYPE_10__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
MR_PopulateDrvRaidMap(struct mrsas_softc *sc)
{
	MR_FW_RAID_MAP_ALL *fw_map_old = NULL;
	MR_FW_RAID_MAP_EXT *fw_map_ext;
	MR_FW_RAID_MAP *pFwRaidMap = NULL;
	unsigned int i;
	u_int16_t ld_count;

	MR_DRV_RAID_MAP_ALL *drv_map = sc->ld_drv_map[(sc->map_id & 1)];
	MR_DRV_RAID_MAP *pDrvRaidMap = &drv_map->raidMap;

	if (sc->maxRaidMapSize) {
		return MR_PopulateDrvRaidMapVentura(sc);
	} else if (sc->max256vdSupport) {
		fw_map_ext = (MR_FW_RAID_MAP_EXT *) sc->raidmap_mem[(sc->map_id & 1)];
		ld_count = (u_int16_t)(fw_map_ext->ldCount);
		if (ld_count > MAX_LOGICAL_DRIVES_EXT) {
			device_printf(sc->mrsas_dev,
			    "mrsas: LD count exposed in RAID map in not valid\n");
			return 1;
		}
#if VD_EXT_DEBUG
		for (i = 0; i < ld_count; i++) {
			printf("mrsas : Index 0x%x Target Id 0x%x Seq Num 0x%x Size 0/%lx\n",
			    i, fw_map_ext->ldSpanMap[i].ldRaid.targetId,
			    fw_map_ext->ldSpanMap[i].ldRaid.seqNum,
			    fw_map_ext->ldSpanMap[i].ldRaid.size);
		}
#endif
		memset(drv_map, 0, sc->drv_map_sz);
		pDrvRaidMap->ldCount = ld_count;
		pDrvRaidMap->fpPdIoTimeoutSec = fw_map_ext->fpPdIoTimeoutSec;
		for (i = 0; i < (MAX_LOGICAL_DRIVES_EXT); i++) {
			pDrvRaidMap->ldTgtIdToLd[i] = (u_int16_t)fw_map_ext->ldTgtIdToLd[i];
		}
		memcpy(pDrvRaidMap->ldSpanMap, fw_map_ext->ldSpanMap, sizeof(MR_LD_SPAN_MAP) * ld_count);
#if VD_EXT_DEBUG
		for (i = 0; i < ld_count; i++) {
			printf("mrsas(%d) : fw_map_ext->ldSpanMap[%d].ldRaid.targetId 0x%x "
			    "fw_map_ext->ldSpanMap[%d].ldRaid.seqNum 0x%x size 0x%x\n",
			    i, i, fw_map_ext->ldSpanMap[i].ldRaid.targetId, i,
			    fw_map_ext->ldSpanMap[i].ldRaid.seqNum,
			    (u_int32_t)fw_map_ext->ldSpanMap[i].ldRaid.rowSize);
			printf("mrsas(%d) : pDrvRaidMap->ldSpanMap[%d].ldRaid.targetId 0x%x"
			    "pDrvRaidMap->ldSpanMap[%d].ldRaid.seqNum 0x%x size 0x%x\n", i, i,
			    pDrvRaidMap->ldSpanMap[i].ldRaid.targetId, i,
			    pDrvRaidMap->ldSpanMap[i].ldRaid.seqNum,
			    (u_int32_t)pDrvRaidMap->ldSpanMap[i].ldRaid.rowSize);
			printf("mrsas : drv raid map all %p raid map %p LD RAID MAP %p/%p\n",
			    drv_map, pDrvRaidMap, &fw_map_ext->ldSpanMap[i].ldRaid,
			    &pDrvRaidMap->ldSpanMap[i].ldRaid);
		}
#endif
		memcpy(pDrvRaidMap->arMapInfo, fw_map_ext->arMapInfo,
		    sizeof(MR_ARRAY_INFO) * MAX_API_ARRAYS_EXT);
		memcpy(pDrvRaidMap->devHndlInfo, fw_map_ext->devHndlInfo,
		    sizeof(MR_DEV_HANDLE_INFO) * MAX_RAIDMAP_PHYSICAL_DEVICES);

		pDrvRaidMap->totalSize = sizeof(MR_FW_RAID_MAP_EXT);
	} else {
		fw_map_old = (MR_FW_RAID_MAP_ALL *) sc->raidmap_mem[(sc->map_id & 1)];
		pFwRaidMap = &fw_map_old->raidMap;

#if VD_EXT_DEBUG
		for (i = 0; i < pFwRaidMap->ldCount; i++) {
			device_printf(sc->mrsas_dev,
			    "Index 0x%x Target Id 0x%x Seq Num 0x%x Size 0/%lx\n", i,
			    fw_map_old->raidMap.ldSpanMap[i].ldRaid.targetId,
			    fw_map_old->raidMap.ldSpanMap[i].ldRaid.seqNum,
			    fw_map_old->raidMap.ldSpanMap[i].ldRaid.size);
		}
#endif

		memset(drv_map, 0, sc->drv_map_sz);
		pDrvRaidMap->totalSize = pFwRaidMap->totalSize;
		pDrvRaidMap->ldCount = pFwRaidMap->ldCount;
		pDrvRaidMap->fpPdIoTimeoutSec =
		    pFwRaidMap->fpPdIoTimeoutSec;

		for (i = 0; i < MAX_RAIDMAP_LOGICAL_DRIVES + MAX_RAIDMAP_VIEWS; i++) {
			pDrvRaidMap->ldTgtIdToLd[i] =
			    (u_int8_t)pFwRaidMap->ldTgtIdToLd[i];
		}

		for (i = 0; i < pDrvRaidMap->ldCount; i++) {
			pDrvRaidMap->ldSpanMap[i] =
			    pFwRaidMap->ldSpanMap[i];

#if VD_EXT_DEBUG
			device_printf(sc->mrsas_dev, "pFwRaidMap->ldSpanMap[%d].ldRaid.targetId 0x%x "
			    "pFwRaidMap->ldSpanMap[%d].ldRaid.seqNum 0x%x size 0x%x\n",
			    i, i, pFwRaidMap->ldSpanMap[i].ldRaid.targetId,
			    pFwRaidMap->ldSpanMap[i].ldRaid.seqNum,
			    (u_int32_t)pFwRaidMap->ldSpanMap[i].ldRaid.rowSize);
			device_printf(sc->mrsas_dev, "pDrvRaidMap->ldSpanMap[%d].ldRaid.targetId 0x%x"
			    "pDrvRaidMap->ldSpanMap[%d].ldRaid.seqNum 0x%x size 0x%x\n", i, i,
			    pDrvRaidMap->ldSpanMap[i].ldRaid.targetId,
			    pDrvRaidMap->ldSpanMap[i].ldRaid.seqNum,
			    (u_int32_t)pDrvRaidMap->ldSpanMap[i].ldRaid.rowSize);
			device_printf(sc->mrsas_dev, "drv raid map all %p raid map %p LD RAID MAP %p/%p\n",
			    drv_map, pDrvRaidMap,
			    &pFwRaidMap->ldSpanMap[i].ldRaid, &pDrvRaidMap->ldSpanMap[i].ldRaid);
#endif
		}

		memcpy(pDrvRaidMap->arMapInfo, pFwRaidMap->arMapInfo,
		    sizeof(MR_ARRAY_INFO) * MAX_RAIDMAP_ARRAYS);
		memcpy(pDrvRaidMap->devHndlInfo, pFwRaidMap->devHndlInfo,
		    sizeof(MR_DEV_HANDLE_INFO) *
		    MAX_RAIDMAP_PHYSICAL_DEVICES);
	}
	return 0;
}