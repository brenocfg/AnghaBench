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
struct ibv_srq_attr {int dummy; } ;
struct ibv_srq_1_0 {int /*<<< orphan*/  real_srq; } ;

/* Variables and functions */
 int ibv_modify_srq (int /*<<< orphan*/ ,struct ibv_srq_attr*,int) ; 

int __ibv_modify_srq_1_0(struct ibv_srq_1_0 *srq,
			 struct ibv_srq_attr *srq_attr,
			 int srq_attr_mask)
{
	return ibv_modify_srq(srq->real_srq, srq_attr, srq_attr_mask);
}