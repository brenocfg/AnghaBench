#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {scalar_t__ srq_id_offset; } ;

/* Variables and functions */

u16 ecore_rdma_get_fw_srq_id(struct ecore_hwfn *p_hwfn, u16 id, bool is_xrc)
{
	if (is_xrc)
		return id;

	return id + p_hwfn->p_rdma_info->srq_id_offset;
}