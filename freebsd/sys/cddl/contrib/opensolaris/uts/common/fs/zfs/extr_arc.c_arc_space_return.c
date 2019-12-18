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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int arc_space_type_t ;

/* Variables and functions */
#define  ARC_SPACE_BONUS 134 
#define  ARC_SPACE_DATA 133 
#define  ARC_SPACE_DBUF 132 
#define  ARC_SPACE_DNODE 131 
#define  ARC_SPACE_HDRS 130 
#define  ARC_SPACE_L2HDRS 129 
#define  ARC_SPACE_META 128 
 int ARC_SPACE_NUMTYPES ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  aggsum_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ aggsum_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ aggsum_upper_bound (int /*<<< orphan*/ *) ; 
 scalar_t__ arc_meta_max ; 
 int /*<<< orphan*/  arc_meta_used ; 
 int /*<<< orphan*/  arc_size ; 
 int /*<<< orphan*/  astat_bonus_size ; 
 int /*<<< orphan*/  astat_data_size ; 
 int /*<<< orphan*/  astat_dbuf_size ; 
 int /*<<< orphan*/  astat_dnode_size ; 
 int /*<<< orphan*/  astat_hdr_size ; 
 int /*<<< orphan*/  astat_l2_hdr_size ; 
 int /*<<< orphan*/  astat_metadata_size ; 

void
arc_space_return(uint64_t space, arc_space_type_t type)
{
	ASSERT(type >= 0 && type < ARC_SPACE_NUMTYPES);

	switch (type) {
	case ARC_SPACE_DATA:
		aggsum_add(&astat_data_size, -space);
		break;
	case ARC_SPACE_META:
		aggsum_add(&astat_metadata_size, -space);
		break;
	case ARC_SPACE_BONUS:
		aggsum_add(&astat_bonus_size, -space);
		break;
	case ARC_SPACE_DNODE:
		aggsum_add(&astat_dnode_size, -space);
		break;
	case ARC_SPACE_DBUF:
		aggsum_add(&astat_dbuf_size, -space);
		break;
	case ARC_SPACE_HDRS:
		aggsum_add(&astat_hdr_size, -space);
		break;
	case ARC_SPACE_L2HDRS:
		aggsum_add(&astat_l2_hdr_size, -space);
		break;
	}

	if (type != ARC_SPACE_DATA) {
		ASSERT(aggsum_compare(&arc_meta_used, space) >= 0);
		/*
		 * We use the upper bound here rather than the precise value
		 * because the arc_meta_max value doesn't need to be
		 * precise. It's only consumed by humans via arcstats.
		 */
		if (arc_meta_max < aggsum_upper_bound(&arc_meta_used))
			arc_meta_max = aggsum_upper_bound(&arc_meta_used);
		aggsum_add(&arc_meta_used, -space);
	}

	ASSERT(aggsum_compare(&arc_size, space) >= 0);
	aggsum_add(&arc_size, -space);
}