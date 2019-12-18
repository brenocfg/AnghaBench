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
struct ibv_qp_init_attr {int dummy; } ;
struct ibv_qp {int dummy; } ;
struct ibv_pd {TYPE_1__* context; } ;
struct c4iw_dev {scalar_t__ abi_version; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct ibv_qp* create_qp (struct ibv_pd*,struct ibv_qp_init_attr*) ; 
 struct ibv_qp* create_qp_v0 (struct ibv_pd*,struct ibv_qp_init_attr*) ; 
 struct c4iw_dev* to_c4iw_dev (int /*<<< orphan*/ ) ; 

struct ibv_qp *c4iw_create_qp(struct ibv_pd *pd,
				     struct ibv_qp_init_attr *attr)
{
	struct c4iw_dev *dev = to_c4iw_dev(pd->context->device);

	if (dev->abi_version == 0)
		return create_qp_v0(pd, attr);
	return create_qp(pd, attr);
}