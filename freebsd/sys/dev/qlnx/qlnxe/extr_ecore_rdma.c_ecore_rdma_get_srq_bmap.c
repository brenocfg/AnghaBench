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
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
struct ecore_bmap {int dummy; } ;
struct TYPE_2__ {struct ecore_bmap srq_map; struct ecore_bmap xrc_srq_map; } ;

/* Variables and functions */

__attribute__((used)) static struct ecore_bmap *ecore_rdma_get_srq_bmap(struct ecore_hwfn *p_hwfn, bool is_xrc)
{
	if (is_xrc)
		return &p_hwfn->p_rdma_info->xrc_srq_map;

	return &p_hwfn->p_rdma_info->srq_map;
}