#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int64_t ;
typedef  size_t u_int32_t ;
struct mrsas_softc {TYPE_5__* log_to_span; } ;
struct TYPE_19__ {scalar_t__ span_row_data_width; scalar_t__ data_strip_end; scalar_t__ data_strip_start; size_t* strip_offset; } ;
struct TYPE_15__ {TYPE_3__* ldSpanMap; } ;
struct TYPE_18__ {TYPE_4__ raidMap; } ;
struct TYPE_17__ {size_t spanDepth; } ;
struct TYPE_16__ {TYPE_8__* span_set; } ;
struct TYPE_14__ {TYPE_2__* spanBlock; } ;
struct TYPE_12__ {size_t noElements; } ;
struct TYPE_13__ {TYPE_1__ block_span_info; } ;
typedef  TYPE_5__* PLD_SPAN_INFO ;
typedef  TYPE_6__ MR_LD_RAID ;
typedef  TYPE_7__ MR_DRV_RAID_MAP_ALL ;
typedef  TYPE_8__ LD_SPAN_SET ;

/* Variables and functions */
 size_t MAX_QUAD_DEPTH ; 
 int /*<<< orphan*/  MRSAS_PRL11 ; 
 TYPE_6__* MR_LdRaidGet (size_t,TYPE_7__*) ; 
 scalar_t__ mega_mod64 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mrsas_dprint (struct mrsas_softc*,int /*<<< orphan*/ ,char*,size_t,unsigned long,...) ; 

__attribute__((used)) static u_int32_t
get_arm_from_strip(struct mrsas_softc *sc,
    u_int32_t ld, u_int64_t strip, MR_DRV_RAID_MAP_ALL * map)
{
	MR_LD_RAID *raid = MR_LdRaidGet(ld, map);
	LD_SPAN_SET *span_set;
	PLD_SPAN_INFO ldSpanInfo = sc->log_to_span;
	u_int32_t info, strip_offset, span, span_offset;

	for (info = 0; info < MAX_QUAD_DEPTH; info++) {
		span_set = &(ldSpanInfo[ld].span_set[info]);

		if (span_set->span_row_data_width == 0)
			break;
		if (strip > span_set->data_strip_end)
			continue;

		strip_offset = (u_int32_t)mega_mod64
		    ((strip - span_set->data_strip_start),
		    span_set->span_row_data_width);

		for (span = 0, span_offset = 0; span < raid->spanDepth; span++)
			if (map->raidMap.ldSpanMap[ld].spanBlock[span].
			    block_span_info.noElements >= info + 1) {
				if (strip_offset >= span_set->strip_offset[span])
					span_offset = span_set->strip_offset[span];
				else
					break;
			}
		mrsas_dprint(sc, MRSAS_PRL11, "AVAGO PRL11: get_arm_from_strip: "
		    "for ld=0x%x strip=0x%lx arm is  0x%x\n", ld,
		    (long unsigned int)strip, (strip_offset - span_offset));
		return (strip_offset - span_offset);
	}

	mrsas_dprint(sc, MRSAS_PRL11, "AVAGO Debug: - get_arm_from_strip: returns invalid arm"
	    " for ld=%x strip=%lx\n", ld, (long unsigned int)strip);

	return -1;
}