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
typedef  int /*<<< orphan*/  u64 ;
struct res_common {int /*<<< orphan*/  from_state; int /*<<< orphan*/  state; } ;
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_resource { ____Placeholder_mlx4_resource } mlx4_resource ;

/* Variables and functions */
 struct res_common* find_res (struct mlx4_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_tlock (struct mlx4_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_res(struct mlx4_dev *dev, int slave, u64 res_id,
		    enum mlx4_resource type)
{
	struct res_common *r;

	spin_lock_irq(mlx4_tlock(dev));
	r = find_res(dev, res_id, type);
	if (r)
		r->state = r->from_state;
	spin_unlock_irq(mlx4_tlock(dev));
}