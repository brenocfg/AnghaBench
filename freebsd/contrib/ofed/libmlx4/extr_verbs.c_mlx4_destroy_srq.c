#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ibv_srq {int /*<<< orphan*/  context; } ;
struct TYPE_3__ {struct TYPE_3__* wrid; int /*<<< orphan*/  buf; int /*<<< orphan*/  db; scalar_t__ ext_srq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_DB_TYPE_RQ ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int ibv_cmd_destroy_srq (struct ibv_srq*) ; 
 int mlx4_destroy_xrc_srq (struct ibv_srq*) ; 
 int /*<<< orphan*/  mlx4_free_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_free_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mctx (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_msrq (struct ibv_srq*) ; 

int mlx4_destroy_srq(struct ibv_srq *srq)
{
	int ret;

	if (to_msrq(srq)->ext_srq)
		return mlx4_destroy_xrc_srq(srq);

	ret = ibv_cmd_destroy_srq(srq);
	if (ret)
		return ret;

	mlx4_free_db(to_mctx(srq->context), MLX4_DB_TYPE_RQ, to_msrq(srq)->db);
	mlx4_free_buf(&to_msrq(srq)->buf);
	free(to_msrq(srq)->wrid);
	free(to_msrq(srq));

	return 0;
}