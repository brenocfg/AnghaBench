#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int last_pkey_idx; } ;
typedef  TYPE_1__ osm_pkey_tbl_t ;

/* Variables and functions */
 int IB_NUM_PKEY_ELEMENTS_IN_BLOCK ; 

__attribute__((used)) static int last_accum_pkey_index(osm_pkey_tbl_t * p_pkey_tbl,
				 uint16_t * p_block_idx,
				 uint8_t * p_pkey_idx)
{
	if (p_pkey_tbl->last_pkey_idx) {
		*p_block_idx = (p_pkey_tbl->last_pkey_idx - 1) / IB_NUM_PKEY_ELEMENTS_IN_BLOCK;
		*p_pkey_idx = (p_pkey_tbl->last_pkey_idx - 1) % IB_NUM_PKEY_ELEMENTS_IN_BLOCK;
		return 1;
	}

	return 0;
}