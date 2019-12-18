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
typedef  scalar_t__ u_int64_t ;
typedef  int u_int32_t ;
typedef  scalar_t__ u_int16_t ;
struct mrsas_softc {int map_id; scalar_t__ lb_pending_cmds; scalar_t__ UnevenSpanSupport; int /*<<< orphan*/ ** ld_drv_map; } ;
struct IO_REQUEST_INFO {scalar_t__ ldStartBlock; int numBlocks; int span_arm; int pd_after_lb; int /*<<< orphan*/  ldTgtId; } ;
struct TYPE_6__ {int rowSize; } ;
struct TYPE_5__ {scalar_t__* last_accessed_block; int /*<<< orphan*/ * scsi_pending_cmds; } ;
typedef  TYPE_1__* PLD_LOAD_BALANCE_INFO ;
typedef  TYPE_2__ MR_LD_RAID ;
typedef  int /*<<< orphan*/  MR_DRV_RAID_MAP_ALL ;

/* Variables and functions */
 scalar_t__ ABS_DIFF (scalar_t__,scalar_t__) ; 
 int MR_ArPdGet (int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ MR_DEVHANDLE_INVALID ; 
 TYPE_2__* MR_LdRaidGet (scalar_t__,int /*<<< orphan*/ *) ; 
 int MR_LdSpanArrayGet (scalar_t__,int,int /*<<< orphan*/ *) ; 
 scalar_t__ MR_PdDevHandleGet (int,int /*<<< orphan*/ *) ; 
 scalar_t__ MR_TargetIdToLdGet (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int RAID_CTX_SPANARM_ARM_MASK ; 
 int RAID_CTX_SPANARM_SPAN_MASK ; 
 int RAID_CTX_SPANARM_SPAN_SHIFT ; 
 int SPAN_ROW_SIZE (int /*<<< orphan*/ *,scalar_t__,int) ; 
 scalar_t__ mrsas_atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int) ; 

u_int8_t 
mrsas_get_best_arm_pd(struct mrsas_softc *sc,
    PLD_LOAD_BALANCE_INFO lbInfo, struct IO_REQUEST_INFO *io_info)
{
	MR_LD_RAID *raid;
	MR_DRV_RAID_MAP_ALL *drv_map;
	u_int16_t pd1_devHandle;
	u_int16_t pend0, pend1, ld;
	u_int64_t diff0, diff1;
	u_int8_t bestArm, pd0, pd1, span, arm;
	u_int32_t arRef, span_row_size;

	u_int64_t block = io_info->ldStartBlock;
	u_int32_t count = io_info->numBlocks;

	span = ((io_info->span_arm & RAID_CTX_SPANARM_SPAN_MASK)
	    >> RAID_CTX_SPANARM_SPAN_SHIFT);
	arm = (io_info->span_arm & RAID_CTX_SPANARM_ARM_MASK);

	drv_map = sc->ld_drv_map[(sc->map_id & 1)];
	ld = MR_TargetIdToLdGet(io_info->ldTgtId, drv_map);
	raid = MR_LdRaidGet(ld, drv_map);
	span_row_size = sc->UnevenSpanSupport ?
	    SPAN_ROW_SIZE(drv_map, ld, span) : raid->rowSize;

	arRef = MR_LdSpanArrayGet(ld, span, drv_map);
	pd0 = MR_ArPdGet(arRef, arm, drv_map);
	pd1 = MR_ArPdGet(arRef, (arm + 1) >= span_row_size ?
	    (arm + 1 - span_row_size) : arm + 1, drv_map);

	/* Get PD1 Dev Handle */
	pd1_devHandle = MR_PdDevHandleGet(pd1, drv_map);
	if (pd1_devHandle == MR_DEVHANDLE_INVALID) {
		bestArm = arm;
	} else {
		/* get the pending cmds for the data and mirror arms */
		pend0 = mrsas_atomic_read(&lbInfo->scsi_pending_cmds[pd0]);
		pend1 = mrsas_atomic_read(&lbInfo->scsi_pending_cmds[pd1]);

		/* Determine the disk whose head is nearer to the req. block */
		diff0 = ABS_DIFF(block, lbInfo->last_accessed_block[pd0]);
		diff1 = ABS_DIFF(block, lbInfo->last_accessed_block[pd1]);
		bestArm = (diff0 <= diff1 ? arm : arm ^ 1);

		if ((bestArm == arm && pend0 > pend1 + sc->lb_pending_cmds) ||
		    (bestArm != arm && pend1 > pend0 + sc->lb_pending_cmds))
			bestArm ^= 1;

		/* Update the last accessed block on the correct pd */
		io_info->span_arm = (span << RAID_CTX_SPANARM_SPAN_SHIFT) | bestArm;
		io_info->pd_after_lb = (bestArm == arm) ? pd0 : pd1;
	}

	lbInfo->last_accessed_block[bestArm == arm ? pd0 : pd1] = block + count - 1;
#if SPAN_DEBUG
	if (arm != bestArm)
		printf("AVAGO Debug R1 Load balance occur - span 0x%x arm 0x%x bestArm 0x%x "
		    "io_info->span_arm 0x%x\n",
		    span, arm, bestArm, io_info->span_arm);
#endif

	return io_info->pd_after_lb;
}