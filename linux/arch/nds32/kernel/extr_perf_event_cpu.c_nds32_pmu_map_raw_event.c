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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  PFM_OFFSET_MAGIC_0 ; 
 int /*<<< orphan*/  PFM_OFFSET_MAGIC_1 ; 
 int /*<<< orphan*/  PFM_OFFSET_MAGIC_2 ; 
 int SPAV3_0_SEL_BASE ; 
 int SPAV3_0_SEL_LAST ; 
 int SPAV3_1_SEL_BASE ; 
 int SPAV3_1_SEL_LAST ; 
 int SPAV3_2_SEL_BASE ; 
 int SPAV3_2_SEL_LAST ; 

__attribute__((used)) static int nds32_pmu_map_raw_event(u32 raw_event_mask, u64 config)
{
	int ev_type = (int)(config & raw_event_mask);
	int idx = config >> 8;

	switch (idx) {
	case 0:
		ev_type = PFM_OFFSET_MAGIC_0 + ev_type;
		if (ev_type >= SPAV3_0_SEL_LAST || ev_type <= SPAV3_0_SEL_BASE)
			return -ENOENT;
		break;
	case 1:
		ev_type = PFM_OFFSET_MAGIC_1 + ev_type;
		if (ev_type >= SPAV3_1_SEL_LAST || ev_type <= SPAV3_1_SEL_BASE)
			return -ENOENT;
		break;
	case 2:
		ev_type = PFM_OFFSET_MAGIC_2 + ev_type;
		if (ev_type >= SPAV3_2_SEL_LAST || ev_type <= SPAV3_2_SEL_BASE)
			return -ENOENT;
		break;
	default:
		return -ENOENT;
	}

	return ev_type;
}