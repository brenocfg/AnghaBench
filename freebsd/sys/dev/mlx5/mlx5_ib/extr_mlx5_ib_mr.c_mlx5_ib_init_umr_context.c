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
struct TYPE_2__ {int /*<<< orphan*/  done; } ;
struct mlx5_ib_umr_context {int status; int /*<<< orphan*/  done; TYPE_1__ cqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_umr_done ; 

__attribute__((used)) static inline void mlx5_ib_init_umr_context(struct mlx5_ib_umr_context *context)
{
	context->cqe.done = mlx5_ib_umr_done;
	context->status = -1;
	init_completion(&context->done);
}