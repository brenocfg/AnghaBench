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
typedef  int /*<<< orphan*/  osm_sm_t ;
struct TYPE_3__ {int /*<<< orphan*/  pkey; int /*<<< orphan*/  part_guid_tbl; int /*<<< orphan*/  full_guid_tbl; } ;
typedef  TYPE_1__ osm_prtn_t ;
typedef  int /*<<< orphan*/  osm_physp_t ;
typedef  int /*<<< orphan*/  osm_log_t ;
typedef  int /*<<< orphan*/  ib_net16_t ;
typedef  int /*<<< orphan*/  cl_map_t ;
typedef  scalar_t__ cl_map_iterator_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_hton16 (int) ; 
 scalar_t__ cl_map_end (int /*<<< orphan*/  const*) ; 
 scalar_t__ cl_map_head (int /*<<< orphan*/  const*) ; 
 scalar_t__ cl_map_next (scalar_t__) ; 
 int /*<<< orphan*/ * cl_map_obj (scalar_t__) ; 
 int /*<<< orphan*/  pkey_mgr_process_physical_port (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pkey_mgr_process_partition_table(osm_log_t * p_log, osm_sm_t * sm,
				 const osm_prtn_t * p_prtn,
				 const boolean_t full)
{
	const cl_map_t *p_tbl =
	    full ? &p_prtn->full_guid_tbl : &p_prtn->part_guid_tbl;
	cl_map_iterator_t i, i_next;
	ib_net16_t pkey = p_prtn->pkey;
	osm_physp_t *p_physp;

	if (full)
		pkey |= cl_hton16(0x8000);

	i_next = cl_map_head(p_tbl);
	while (i_next != cl_map_end(p_tbl)) {
		i = i_next;
		i_next = cl_map_next(i);
		p_physp = cl_map_obj(i);
		if (p_physp)
			pkey_mgr_process_physical_port(p_log, sm, pkey,
						       p_physp);
	}
}