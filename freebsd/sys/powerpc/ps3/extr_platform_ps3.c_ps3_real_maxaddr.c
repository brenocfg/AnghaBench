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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  lv1_get_logical_partition_id (scalar_t__*) ; 
 int /*<<< orphan*/  lv1_get_logical_ppe_id (scalar_t__*) ; 
 int /*<<< orphan*/  lv1_get_repository_node_value (scalar_t__,int,int,scalar_t__,int,scalar_t__*,scalar_t__*) ; 
 int lv1_repository_string (char*) ; 

__attribute__((used)) static vm_offset_t
ps3_real_maxaddr(platform_t plat)
{
	uint64_t lpar_id, junk, ppe_id;
	static uint64_t rm_maxaddr = 0;

	if (rm_maxaddr == 0) {
		/* Get real mode memory region */
		lv1_get_logical_partition_id(&lpar_id);
		lv1_get_logical_ppe_id(&ppe_id);

		lv1_get_repository_node_value(lpar_id,
		    lv1_repository_string("bi") >> 32,
		    lv1_repository_string("pu"),
		    ppe_id, lv1_repository_string("rm_size"),
		    &rm_maxaddr, &junk);
	}
	
	return (rm_maxaddr);
}