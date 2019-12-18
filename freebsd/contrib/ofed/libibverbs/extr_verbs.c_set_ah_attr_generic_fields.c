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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct ibv_wc {int /*<<< orphan*/  dlid_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  slid; } ;
struct ibv_grh {int /*<<< orphan*/  version_tclass_flow; } ;
struct TYPE_2__ {int flow_label; } ;
struct ibv_ah_attr {int /*<<< orphan*/  port_num; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  dlid; TYPE_1__ grh; } ;

/* Variables and functions */
 int be32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void set_ah_attr_generic_fields(struct ibv_ah_attr *ah_attr,
					      struct ibv_wc *wc,
					      struct ibv_grh *grh,
					      uint8_t port_num)
{
	uint32_t flow_class;

	flow_class = be32toh(grh->version_tclass_flow);
	ah_attr->grh.flow_label = flow_class & 0xFFFFF;
	ah_attr->dlid = wc->slid;
	ah_attr->sl = wc->sl;
	ah_attr->src_path_bits = wc->dlid_path_bits;
	ah_attr->port_num = port_num;
}