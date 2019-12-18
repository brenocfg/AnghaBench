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
struct ibv_cq {int /*<<< orphan*/  context; } ;
struct TYPE_3__ {int /*<<< orphan*/  active_buf; int /*<<< orphan*/  dbrec; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int ibv_cmd_destroy_cq (struct ibv_cq*) ; 
 int /*<<< orphan*/  mlx5_free_cq_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_free_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mcq (struct ibv_cq*) ; 
 int /*<<< orphan*/  to_mctx (int /*<<< orphan*/ ) ; 

int mlx5_destroy_cq(struct ibv_cq *cq)
{
	int ret;

	ret = ibv_cmd_destroy_cq(cq);
	if (ret)
		return ret;

	mlx5_free_db(to_mctx(cq->context), to_mcq(cq)->dbrec);
	mlx5_free_cq_buf(to_mctx(cq->context), to_mcq(cq)->active_buf);
	free(to_mcq(cq));

	return 0;
}