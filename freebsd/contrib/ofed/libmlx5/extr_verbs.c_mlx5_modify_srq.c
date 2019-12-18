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
struct ibv_srq {int dummy; } ;
struct ibv_modify_srq {int dummy; } ;

/* Variables and functions */
 int ibv_cmd_modify_srq (struct ibv_srq*,struct ibv_srq_attr*,int,struct ibv_modify_srq*,int) ; 

int mlx5_modify_srq(struct ibv_srq *srq,
		    struct ibv_srq_attr *attr,
		    int attr_mask)
{
	struct ibv_modify_srq cmd;

	return ibv_cmd_modify_srq(srq, attr, attr_mask, &cmd, sizeof cmd);
}