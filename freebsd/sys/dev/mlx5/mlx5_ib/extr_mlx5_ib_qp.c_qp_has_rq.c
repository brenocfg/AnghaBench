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
struct TYPE_2__ {int /*<<< orphan*/  max_recv_wr; } ;
struct ib_qp_init_attr {scalar_t__ qp_type; TYPE_1__ cap; scalar_t__ srq; } ;

/* Variables and functions */
 scalar_t__ IB_QPT_XRC_INI ; 
 scalar_t__ IB_QPT_XRC_TGT ; 
 scalar_t__ MLX5_IB_QPT_REG_UMR ; 

__attribute__((used)) static int qp_has_rq(struct ib_qp_init_attr *attr)
{
	if (attr->qp_type == IB_QPT_XRC_INI ||
	    attr->qp_type == IB_QPT_XRC_TGT || attr->srq ||
	    attr->qp_type == MLX5_IB_QPT_REG_UMR ||
	    !attr->cap.max_recv_wr)
		return 0;

	return 1;
}