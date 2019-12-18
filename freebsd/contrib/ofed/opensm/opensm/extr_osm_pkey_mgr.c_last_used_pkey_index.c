#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_12__ {TYPE_2__* p_node; } ;
typedef  TYPE_3__ osm_port_t ;
struct TYPE_13__ {scalar_t__ used_blocks; scalar_t__ max_blocks; } ;
typedef  TYPE_4__ osm_pkey_tbl_t ;
struct TYPE_14__ {int /*<<< orphan*/ * pkey_entry; } ;
typedef  TYPE_5__ ib_pkey_table_t ;
struct TYPE_10__ {int /*<<< orphan*/  partition_cap; } ;
struct TYPE_11__ {TYPE_1__ node_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (size_t*) ; 
 size_t IB_NUM_PKEY_ELEMENTS_IN_BLOCK ; 
 size_t cl_ntoh16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_pkey_is_invalid (int /*<<< orphan*/ ) ; 
 TYPE_5__* osm_pkey_tbl_new_block_get (TYPE_4__ const*,scalar_t__) ; 

__attribute__((used)) static int last_used_pkey_index(const osm_port_t * const p_port,
				const osm_pkey_tbl_t * p_pkey_tbl,
				uint16_t * p_last_index)
{
	ib_pkey_table_t *last_block;
	uint16_t index, last_index = 0;

	CL_ASSERT(p_last_index);

	last_block = osm_pkey_tbl_new_block_get(p_pkey_tbl,
						p_pkey_tbl->used_blocks - 1);
	if (!last_block)
		return 1;

	if (p_pkey_tbl->used_blocks == p_pkey_tbl->max_blocks)
		last_index = cl_ntoh16(p_port->p_node->node_info.partition_cap) % IB_NUM_PKEY_ELEMENTS_IN_BLOCK;
	if (last_index == 0)
		last_index = IB_NUM_PKEY_ELEMENTS_IN_BLOCK;
	index = last_index;
	do {
		index--;
		if (!ib_pkey_is_invalid(last_block->pkey_entry[index]))
			break;
	} while (index != 0);

	*p_last_index = index;
	return 0;
}