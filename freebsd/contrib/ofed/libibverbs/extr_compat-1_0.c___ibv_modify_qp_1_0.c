#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ibv_qp_attr {int dummy; } ;
struct ibv_qp_1_0 {int /*<<< orphan*/  real_qp; } ;

/* Variables and functions */
 int ibv_modify_qp (int /*<<< orphan*/ ,struct ibv_qp_attr*,int) ; 

int __ibv_modify_qp_1_0(struct ibv_qp_1_0 *qp, struct ibv_qp_attr *attr,
			int attr_mask)
{
	return ibv_modify_qp(qp->real_qp, attr, attr_mask);
}