#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_ib_ucontext {int /*<<< orphan*/  uuari; } ;
struct TYPE_4__ {scalar_t__ umem; } ;
struct mlx5_ib_qp_base {TYPE_2__ ubuffer; } ;
struct mlx5_ib_qp {int /*<<< orphan*/  uuarn; int /*<<< orphan*/  db; } ;
struct ib_pd {TYPE_1__* uobject; } ;
struct TYPE_3__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_uuar (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_release (scalar_t__) ; 
 int /*<<< orphan*/  mlx5_ib_db_unmap_user (struct mlx5_ib_ucontext*,int /*<<< orphan*/ *) ; 
 struct mlx5_ib_ucontext* to_mucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_qp_user(struct ib_pd *pd, struct mlx5_ib_qp *qp,
			    struct mlx5_ib_qp_base *base)
{
	struct mlx5_ib_ucontext *context;

	context = to_mucontext(pd->uobject->context);
	mlx5_ib_db_unmap_user(context, &qp->db);
	if (base->ubuffer.umem)
		ib_umem_release(base->ubuffer.umem);
	free_uuar(&context->uuari, qp->uuarn);
}