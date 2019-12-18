#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_6__ {int /*<<< orphan*/  new_blocks; } ;
typedef  TYPE_1__ osm_pkey_tbl_t ;
struct TYPE_7__ {scalar_t__* pkey_entry; } ;
typedef  TYPE_2__ ib_pkey_table_t ;
typedef  scalar_t__ ib_net16_t ;

/* Variables and functions */
 scalar_t__ IB_NUM_PKEY_ELEMENTS_IN_BLOCK ; 
 scalar_t__ cl_ptr_vector_get_size (int /*<<< orphan*/ *) ; 
 TYPE_2__* osm_pkey_tbl_new_block_get (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static int new_pkey_exists(osm_pkey_tbl_t * p_pkey_tbl, ib_net16_t pkey)
{
	uint16_t num_blocks;
	uint16_t block_index;
	ib_pkey_table_t *block;
	uint16_t pkey_idx;

	num_blocks = (uint16_t) cl_ptr_vector_get_size(&p_pkey_tbl->new_blocks);
	for (block_index = 0; block_index < num_blocks; block_index++) {
		block = osm_pkey_tbl_new_block_get(p_pkey_tbl, block_index);
		if (!block)
			continue;

		for (pkey_idx = 0; pkey_idx < IB_NUM_PKEY_ELEMENTS_IN_BLOCK;
		     pkey_idx++) {
			if (block->pkey_entry[pkey_idx] == pkey)
				return 1;
		}
	}
	return 0;
}