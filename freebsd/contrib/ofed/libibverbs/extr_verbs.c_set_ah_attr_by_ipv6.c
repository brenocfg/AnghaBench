#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int* raw; } ;
struct ibv_grh {scalar_t__ next_hdr; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  version_tclass_flow; TYPE_2__ dgid; int /*<<< orphan*/  sgid; } ;
struct ibv_context {int dummy; } ;
struct TYPE_3__ {int traffic_class; int /*<<< orphan*/  hop_limit; scalar_t__ sgid_index; int /*<<< orphan*/  dgid; } ;
struct ibv_ah_attr {TYPE_1__ grh; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPROTONOSUPPORT ; 
 int IBV_GID_TYPE_IB_ROCE_V1 ; 
 int IBV_GID_TYPE_ROCE_V2 ; 
 scalar_t__ IB_NEXT_HDR ; 
 scalar_t__ IPPROTO_UDP ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int ibv_find_gid_index (struct ibv_context*,scalar_t__,TYPE_2__*,int) ; 

__attribute__((used)) static inline int set_ah_attr_by_ipv6(struct ibv_context *context,
				  struct ibv_ah_attr *ah_attr,
				  struct ibv_grh *grh, uint8_t port_num)
{
	uint32_t flow_class;
	uint32_t sgid_type;
	int ret;

	/* No point searching multicast GIDs in GID table */
	if (grh->dgid.raw[0] == 0xFF) {
		errno = EINVAL;
		return -1;
	}

	ah_attr->grh.dgid = grh->sgid;
	if (grh->next_hdr == IPPROTO_UDP) {
		sgid_type = IBV_GID_TYPE_ROCE_V2;
	} else if (grh->next_hdr == IB_NEXT_HDR) {
		sgid_type = IBV_GID_TYPE_IB_ROCE_V1;
	} else {
		errno = EPROTONOSUPPORT;
		return -1;
	}

	ret = ibv_find_gid_index(context, port_num, &grh->dgid,
				 sgid_type);
	if (ret < 0)
		return ret;

	ah_attr->grh.sgid_index = (uint8_t) ret;
	flow_class = be32toh(grh->version_tclass_flow);
	ah_attr->grh.hop_limit = grh->hop_limit;
	ah_attr->grh.traffic_class = (flow_class >> 20) & 0xFF;

	return 0;
}