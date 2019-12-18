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
struct mlx5_ib_ucontext {int dummy; } ;
struct mlx5_ib_rwq {scalar_t__ umem; int /*<<< orphan*/  db; } ;
struct ib_pd {TYPE_1__* uobject; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umem_release (scalar_t__) ; 
 int /*<<< orphan*/  mlx5_ib_db_unmap_user (struct mlx5_ib_ucontext*,int /*<<< orphan*/ *) ; 
 struct mlx5_ib_ucontext* to_mucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_user_rq(struct ib_pd *pd, struct mlx5_ib_rwq *rwq)
{
	struct mlx5_ib_ucontext *context;

	context = to_mucontext(pd->uobject->context);
	mlx5_ib_db_unmap_user(context, &rwq->db);
	if (rwq->umem)
		ib_umem_release(rwq->umem);
}