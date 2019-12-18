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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ecore_tid_seg {int has_fl_mem; size_t type; int /*<<< orphan*/  count; } ;
struct ecore_hwfn {struct ecore_cxt_mngr* p_cxt_mngr; } ;
struct ecore_cxt_mngr {TYPE_1__* conn_cfg; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;
struct TYPE_2__ {struct ecore_tid_seg* tid_seg; } ;

/* Variables and functions */

__attribute__((used)) static void ecore_cxt_set_proto_tid_count(struct ecore_hwfn *p_hwfn,
					  enum protocol_type proto,
					  u8 seg,
					  u8 seg_type,
					  u32 count,
					  bool has_fl)
{
	struct ecore_cxt_mngr *p_mngr = p_hwfn->p_cxt_mngr;
	struct ecore_tid_seg *p_seg = &p_mngr->conn_cfg[proto].tid_seg[seg];

	p_seg->count = count;
	p_seg->has_fl_mem = has_fl;
	p_seg->type = seg_type;
}