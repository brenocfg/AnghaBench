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
struct node_caps {int arr_sz; int /*<<< orphan*/ * caps; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FLOW_TABLE_CAP (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool has_required_caps(struct mlx5_core_dev *dev, struct node_caps *caps)
{
	int i;

	for (i = 0; i < caps->arr_sz; i++) {
		if (!GET_FLOW_TABLE_CAP(dev, caps->caps[i]))
			return false;
	}
	return true;
}