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
struct mlx4_ib_dev {TYPE_1__* diag_counters; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int MLX4_DIAG_COUNTERS_TYPES ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx4_ib_diag_cleanup(struct mlx4_ib_dev *ibdev)
{
	int i;

	for (i = 0; i < MLX4_DIAG_COUNTERS_TYPES; i++) {
		kfree(ibdev->diag_counters[i].offset);
		kfree(ibdev->diag_counters[i].name);
	}
}