#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int64_t ;
typedef  scalar_t__ u_int32_t ;
struct TYPE_10__ {scalar_t__ spanDepth; scalar_t__ stripeShift; } ;
struct TYPE_9__ {scalar_t__ diff; scalar_t__ logStart; scalar_t__ logEnd; scalar_t__ offsetInSpan; } ;
struct TYPE_7__ {scalar_t__ noElements; TYPE_3__* quad; } ;
struct TYPE_8__ {TYPE_1__ block_span_info; } ;
typedef  TYPE_2__ MR_SPAN_BLOCK_INFO ;
typedef  TYPE_3__ MR_QUAD_ELEMENT ;
typedef  TYPE_4__ MR_LD_RAID ;
typedef  int /*<<< orphan*/  MR_DRV_RAID_MAP_ALL ;

/* Variables and functions */
 TYPE_4__* MR_LdRaidGet (scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_2__* MR_LdSpanInfoGet (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ mega_div64_32 (scalar_t__,scalar_t__) ; 
 scalar_t__ mega_mod64 (scalar_t__,scalar_t__) ; 

u_int32_t
MR_GetSpanBlock(u_int32_t ld, u_int64_t row, u_int64_t *span_blk,
    MR_DRV_RAID_MAP_ALL * map, int *div_error)
{
	MR_SPAN_BLOCK_INFO *pSpanBlock = MR_LdSpanInfoGet(ld, map);
	MR_QUAD_ELEMENT *quad;
	MR_LD_RAID *raid = MR_LdRaidGet(ld, map);
	u_int32_t span, j;
	u_int64_t blk, debugBlk;

	for (span = 0; span < raid->spanDepth; span++, pSpanBlock++) {
		for (j = 0; j < pSpanBlock->block_span_info.noElements; j++) {
			quad = &pSpanBlock->block_span_info.quad[j];
			if (quad->diff == 0) {
				*div_error = 1;
				return span;
			}
			if (quad->logStart <= row && row <= quad->logEnd &&
			    (mega_mod64(row - quad->logStart, quad->diff)) == 0) {
				if (span_blk != NULL) {
					blk = mega_div64_32((row - quad->logStart), quad->diff);
					debugBlk = blk;
					blk = (blk + quad->offsetInSpan) << raid->stripeShift;
					*span_blk = blk;
				}
				return span;
			}
		}
	}
	return span;
}