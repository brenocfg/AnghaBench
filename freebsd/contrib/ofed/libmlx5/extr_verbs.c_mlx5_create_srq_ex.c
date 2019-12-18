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
struct ibv_srq_init_attr_ex {int comp_mask; scalar_t__ srq_type; int /*<<< orphan*/  pd; } ;
struct ibv_srq_init_attr {int dummy; } ;
struct ibv_srq {int dummy; } ;
struct ibv_context {int dummy; } ;

/* Variables and functions */
 scalar_t__ IBV_SRQT_BASIC ; 
 scalar_t__ IBV_SRQT_XRC ; 
 int IBV_SRQ_INIT_ATTR_TYPE ; 
 struct ibv_srq* mlx5_create_srq (int /*<<< orphan*/ ,struct ibv_srq_init_attr*) ; 
 struct ibv_srq* mlx5_create_xrc_srq (struct ibv_context*,struct ibv_srq_init_attr_ex*) ; 

struct ibv_srq *mlx5_create_srq_ex(struct ibv_context *context,
				   struct ibv_srq_init_attr_ex *attr)
{
	if (!(attr->comp_mask & IBV_SRQ_INIT_ATTR_TYPE) ||
	    (attr->srq_type == IBV_SRQT_BASIC))
		return mlx5_create_srq(attr->pd,
				       (struct ibv_srq_init_attr *)attr);
	else if (attr->srq_type == IBV_SRQT_XRC)
		return mlx5_create_xrc_srq(context, attr);

	return NULL;
}