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
struct mlx4_ib_ucontext {int /*<<< orphan*/  uar; } ;
struct ib_ucontext {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx4_ib_ucontext*) ; 
 int /*<<< orphan*/  mlx4_uar_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_ucontext* to_mucontext (struct ib_ucontext*) ; 

__attribute__((used)) static int mlx4_ib_dealloc_ucontext(struct ib_ucontext *ibcontext)
{
	struct mlx4_ib_ucontext *context = to_mucontext(ibcontext);

	mlx4_uar_free(to_mdev(ibcontext->device)->dev, &context->uar);
	kfree(context);

	return 0;
}