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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 int /*<<< orphan*/  lv1_get_logical_ppe_id (scalar_t__*) ; 
 int ps3_repository_read_region_total (scalar_t__*) ; 
 int ps3_repository_read_rm_size (scalar_t__,scalar_t__*) ; 

int ps3_repository_read_mm_info(u64 *rm_base, u64 *rm_size, u64 *region_total)
{
	int result;
	u64 ppe_id;

	lv1_get_logical_ppe_id(&ppe_id);
	*rm_base = 0;
	result = ps3_repository_read_rm_size(ppe_id, rm_size);
	return result ? result
		: ps3_repository_read_region_total(region_total);
}