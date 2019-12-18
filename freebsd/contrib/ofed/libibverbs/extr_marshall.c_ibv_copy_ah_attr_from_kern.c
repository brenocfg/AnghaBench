#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dgid; } ;
struct ibv_kern_ah_attr {int /*<<< orphan*/  port_num; int /*<<< orphan*/  is_global; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; TYPE_3__ grh; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct TYPE_5__ {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; TYPE_1__ dgid; } ;
struct ibv_ah_attr {int /*<<< orphan*/  port_num; int /*<<< orphan*/  is_global; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; TYPE_2__ grh; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ibv_copy_ah_attr_from_kern(struct ibv_ah_attr *dst,
				struct ibv_kern_ah_attr *src)
{
	memcpy(dst->grh.dgid.raw, src->grh.dgid, sizeof dst->grh.dgid);
	dst->grh.flow_label = src->grh.flow_label;
	dst->grh.sgid_index = src->grh.sgid_index;
	dst->grh.hop_limit = src->grh.hop_limit;
	dst->grh.traffic_class = src->grh.traffic_class;

	dst->dlid = src->dlid;
	dst->sl = src->sl;
	dst->src_path_bits = src->src_path_bits;
	dst->static_rate = src->static_rate;
	dst->is_global = src->is_global;
	dst->port_num = src->port_num;
}