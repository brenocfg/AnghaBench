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
struct mlx5_ib_srq {int /*<<< orphan*/  umem; int /*<<< orphan*/  db; } ;
struct ib_pd {TYPE_1__* uobject; } ;
struct TYPE_2__ {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_db_unmap_user (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_mucontext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void destroy_srq_user(struct ib_pd *pd, struct mlx5_ib_srq *srq)
{
	mlx5_ib_db_unmap_user(to_mucontext(pd->uobject->context), &srq->db);
	ib_umem_release(srq->umem);
}