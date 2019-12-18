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
struct ibv_qp_init_attr_ex {int dummy; } ;
struct ibv_qp {int dummy; } ;
struct ibv_context {int dummy; } ;

/* Variables and functions */
 struct ibv_qp* create_qp (struct ibv_context*,struct ibv_qp_init_attr_ex*) ; 

struct ibv_qp *mlx5_create_qp_ex(struct ibv_context *context,
				 struct ibv_qp_init_attr_ex *attr)
{
	return create_qp(context, attr);
}