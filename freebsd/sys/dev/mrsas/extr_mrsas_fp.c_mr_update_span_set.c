#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_15__ ;

/* Type definitions */
typedef  size_t u_int8_t ;
typedef  int u_int64_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct TYPE_28__ {int diff; int* strip_offset; int span_row_data_width; int log_start_lba; int log_end_lba; int span_row_start; int span_row_end; int data_strip_start; int data_strip_end; int data_row_start; int data_row_end; } ;
struct TYPE_23__ {TYPE_3__* ldSpanMap; } ;
struct TYPE_27__ {TYPE_4__ raidMap; } ;
struct TYPE_26__ {size_t spanDepth; int stripeShift; } ;
struct TYPE_25__ {int diff; scalar_t__ logStart; scalar_t__ logEnd; } ;
struct TYPE_24__ {TYPE_9__* span_set; } ;
struct TYPE_22__ {TYPE_2__* spanBlock; } ;
struct TYPE_20__ {int noElements; TYPE_6__* quad; } ;
struct TYPE_21__ {TYPE_1__ block_span_info; } ;
struct TYPE_19__ {int spanRowDataSize; } ;
typedef  TYPE_5__* PLD_SPAN_INFO ;
typedef  TYPE_6__ MR_QUAD_ELEMENT ;
typedef  TYPE_7__ MR_LD_RAID ;
typedef  TYPE_8__ MR_DRV_RAID_MAP_ALL ;
typedef  TYPE_9__ LD_SPAN_SET ;

/* Variables and functions */
 int MAX_LOGICAL_DRIVES ; 
 int MAX_QUAD_DEPTH ; 
 TYPE_7__* MR_LdRaidGet (int,TYPE_8__*) ; 
 TYPE_15__* MR_LdSpanPtrGet (int,size_t,TYPE_8__*) ; 
 int MR_TargetIdToLdGet (int,TYPE_8__*) ; 
 int /*<<< orphan*/  getSpanInfo (TYPE_8__*,TYPE_5__*) ; 
 int mega_div64_32 (scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,size_t,int) ; 

void
mr_update_span_set(MR_DRV_RAID_MAP_ALL * map, PLD_SPAN_INFO ldSpanInfo)
{
	u_int8_t span, count;
	u_int32_t element, span_row_width;
	u_int64_t span_row;
	MR_LD_RAID *raid;
	LD_SPAN_SET *span_set, *span_set_prev;
	MR_QUAD_ELEMENT *quad;
	int ldCount;
	u_int16_t ld;

	for (ldCount = 0; ldCount < MAX_LOGICAL_DRIVES; ldCount++) {
		ld = MR_TargetIdToLdGet(ldCount, map);
		if (ld >= MAX_LOGICAL_DRIVES)
			continue;
		raid = MR_LdRaidGet(ld, map);
		for (element = 0; element < MAX_QUAD_DEPTH; element++) {
			for (span = 0; span < raid->spanDepth; span++) {
				if (map->raidMap.ldSpanMap[ld].spanBlock[span].
				    block_span_info.noElements < element + 1)
					continue;
				/* TO-DO */
				span_set = &(ldSpanInfo[ld].span_set[element]);
				quad = &map->raidMap.ldSpanMap[ld].
				    spanBlock[span].block_span_info.quad[element];

				span_set->diff = quad->diff;

				for (count = 0, span_row_width = 0;
				    count < raid->spanDepth; count++) {
					if (map->raidMap.ldSpanMap[ld].spanBlock[count].
					    block_span_info.noElements >= element + 1) {
						span_set->strip_offset[count] = span_row_width;
						span_row_width +=
						    MR_LdSpanPtrGet(ld, count, map)->spanRowDataSize;
#if SPAN_DEBUG
						printf("AVAGO Debug span %x rowDataSize %x\n", count,
						    MR_LdSpanPtrGet(ld, count, map)->spanRowDataSize);
#endif
					}
				}

				span_set->span_row_data_width = span_row_width;
				span_row = mega_div64_32(((quad->logEnd -
				    quad->logStart) + quad->diff), quad->diff);

				if (element == 0) {
					span_set->log_start_lba = 0;
					span_set->log_end_lba =
					    ((span_row << raid->stripeShift) * span_row_width) - 1;

					span_set->span_row_start = 0;
					span_set->span_row_end = span_row - 1;

					span_set->data_strip_start = 0;
					span_set->data_strip_end = (span_row * span_row_width) - 1;

					span_set->data_row_start = 0;
					span_set->data_row_end = (span_row * quad->diff) - 1;
				} else {
					span_set_prev = &(ldSpanInfo[ld].span_set[element - 1]);
					span_set->log_start_lba = span_set_prev->log_end_lba + 1;
					span_set->log_end_lba = span_set->log_start_lba +
					    ((span_row << raid->stripeShift) * span_row_width) - 1;

					span_set->span_row_start = span_set_prev->span_row_end + 1;
					span_set->span_row_end =
					    span_set->span_row_start + span_row - 1;

					span_set->data_strip_start =
					    span_set_prev->data_strip_end + 1;
					span_set->data_strip_end = span_set->data_strip_start +
					    (span_row * span_row_width) - 1;

					span_set->data_row_start = span_set_prev->data_row_end + 1;
					span_set->data_row_end = span_set->data_row_start +
					    (span_row * quad->diff) - 1;
				}
				break;
			}
			if (span == raid->spanDepth)
				break;	/* no quads remain */
		}
	}
#if SPAN_DEBUG
	getSpanInfo(map, ldSpanInfo);	/* to get span set info */
#endif
}