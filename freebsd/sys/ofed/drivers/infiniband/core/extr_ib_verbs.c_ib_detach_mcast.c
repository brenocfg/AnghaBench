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
union ib_gid {scalar_t__ raw; } ;
typedef  int /*<<< orphan*/  u16 ;
struct in6_addr {int dummy; } ;
struct ib_qp {scalar_t__ qp_type; int /*<<< orphan*/  usecnt; TYPE_1__* device; } ;
struct TYPE_2__ {int (* detach_mcast ) (struct ib_qp*,union ib_gid*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 scalar_t__ IB_QPT_UD ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_valid_mcast_lid (struct ib_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_is_multicast_addr (struct in6_addr*) ; 
 int stub1 (struct ib_qp*,union ib_gid*,int /*<<< orphan*/ ) ; 

int ib_detach_mcast(struct ib_qp *qp, union ib_gid *gid, u16 lid)
{
	int ret;

	if (!qp->device->detach_mcast)
		return -ENOSYS;

	if (!rdma_is_multicast_addr((struct in6_addr *)gid->raw) ||
	    qp->qp_type != IB_QPT_UD || !is_valid_mcast_lid(qp, lid))
		return -EINVAL;

	ret = qp->device->detach_mcast(qp, gid, lid);
	if (!ret)
		atomic_dec(&qp->usecnt);
	return ret;
}