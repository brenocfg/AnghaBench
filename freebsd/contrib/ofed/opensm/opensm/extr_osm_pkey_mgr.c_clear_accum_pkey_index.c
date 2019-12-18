#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  uintptr_t uint16_t ;
struct TYPE_4__ {uintptr_t last_pkey_idx; int /*<<< orphan*/  accum_pkeys; } ;
typedef  TYPE_1__ osm_pkey_tbl_t ;
typedef  scalar_t__ cl_map_iterator_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_ASSERT (void*) ; 
 scalar_t__ cl_map_end (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_map_head (int /*<<< orphan*/ *) ; 
 scalar_t__ cl_map_next (scalar_t__) ; 
 scalar_t__ cl_map_obj (scalar_t__) ; 
 int /*<<< orphan*/  cl_map_remove_item (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  osm_pkey_find_last_accum_pkey_index (TYPE_1__*) ; 

__attribute__((used)) static void clear_accum_pkey_index(osm_pkey_tbl_t * p_pkey_tbl,
				   uint16_t pkey_index)
{
	uint16_t pkey_idx_bias, pkey_idx;
	void *ptr;
	uintptr_t pkey_idx_ptr;
	cl_map_iterator_t map_iter, map_iter_temp;

	map_iter = cl_map_head(&p_pkey_tbl->accum_pkeys);

	pkey_idx_bias = pkey_index + 1; // adjust for pkey index bias in accum_pkeys

	while (map_iter != cl_map_end(&p_pkey_tbl->accum_pkeys)) {
		map_iter_temp = cl_map_next(map_iter);
		ptr = (uint16_t *) cl_map_obj(map_iter);
		CL_ASSERT(ptr);
		pkey_idx_ptr = (uintptr_t) ptr;
		pkey_idx = pkey_idx_ptr;
		if (pkey_idx == pkey_idx_bias) {
			cl_map_remove_item(&p_pkey_tbl->accum_pkeys, map_iter);
			if (p_pkey_tbl->last_pkey_idx == pkey_idx)
				osm_pkey_find_last_accum_pkey_index(p_pkey_tbl);
			break;
		}
		map_iter = map_iter_temp;
	}
}