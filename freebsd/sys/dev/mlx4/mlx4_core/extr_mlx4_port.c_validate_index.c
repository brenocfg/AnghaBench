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
struct mlx4_mac_table {int max; int /*<<< orphan*/ * entries; } ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*) ; 

__attribute__((used)) static int validate_index(struct mlx4_dev *dev,
			  struct mlx4_mac_table *table, int index)
{
	int err = 0;

	if (index < 0 || index >= table->max || !table->entries[index]) {
		mlx4_warn(dev, "No valid Mac entry for the given index\n");
		err = -EINVAL;
	}
	return err;
}