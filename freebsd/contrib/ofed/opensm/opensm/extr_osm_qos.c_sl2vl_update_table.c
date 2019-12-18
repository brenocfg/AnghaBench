#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  tbl ;
struct TYPE_13__ {int /*<<< orphan*/  list_item; } ;
typedef  TYPE_1__ qos_mad_item_t ;
typedef  int /*<<< orphan*/  osm_sm_t ;
struct TYPE_14__ {int /*<<< orphan*/  port_info; } ;
typedef  TYPE_2__ osm_physp_t ;
struct TYPE_15__ {int* raw_vl_by_sl; } ;
typedef  TYPE_3__ ib_slvl_table_t ;
typedef  int /*<<< orphan*/  ib_api_status_t ;
typedef  int /*<<< orphan*/  cl_qlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_INSUFFICIENT_MEMORY ; 
 int /*<<< orphan*/  IB_MAD_ATTR_SLVL_TABLE ; 
 int IB_MAX_NUM_VLS ; 
 int /*<<< orphan*/  IB_SUCCESS ; 
 int /*<<< orphan*/  cl_qlist_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ib_port_info_get_op_vls (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* osm_physp_get_slvl_tbl (TYPE_2__*,int) ; 
 TYPE_1__* osm_qos_mad_create (int /*<<< orphan*/ *,TYPE_2__*,int,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ib_api_status_t sl2vl_update_table(osm_sm_t * sm, osm_physp_t * p,
					  uint8_t in_port, uint32_t attr_mod,
					  unsigned force_update,
					  const ib_slvl_table_t * sl2vl_table,
					  cl_qlist_t *mad_list)
{
	ib_slvl_table_t tbl, *p_tbl;
	unsigned vl_mask;
	uint8_t vl1, vl2;
	int i;
	qos_mad_item_t *p_mad;

	vl_mask = (1 << (ib_port_info_get_op_vls(&p->port_info) - 1)) - 1;

	for (i = 0; i < IB_MAX_NUM_VLS / 2; i++) {
		vl1 = sl2vl_table->raw_vl_by_sl[i] >> 4;
		vl2 = sl2vl_table->raw_vl_by_sl[i] & 0xf;
		if (vl1 != 15)
			vl1 &= vl_mask;
		if (vl2 != 15)
			vl2 &= vl_mask;
		tbl.raw_vl_by_sl[i] = (vl1 << 4) | vl2;
	}

	p_tbl = osm_physp_get_slvl_tbl(p, in_port);

	if (!force_update && !memcmp(p_tbl, &tbl, sizeof(tbl)))
		return IB_SUCCESS;

	p_mad = osm_qos_mad_create(sm, p, sizeof(tbl), (uint8_t *) & tbl,
				   IB_MAD_ATTR_SLVL_TABLE, attr_mod);
	if (!p_mad)
		return IB_INSUFFICIENT_MEMORY;

	/*
	 * Zero the stored SL2VL block, so in case the MAD will
	 * end up with error, we will resend it in the next sweep.
	 */
	memset(p_tbl, 0, sizeof(tbl));

	cl_qlist_insert_tail(mad_list, &p_mad->list_item);
	return IB_SUCCESS;
}