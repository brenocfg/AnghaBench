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
struct res_common {scalar_t__ state; int owner; scalar_t__ from_state; } ;
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_resource { ____Placeholder_mlx4_resource } mlx4_resource ;

/* Variables and functions */
 int EBUSY ; 
 int ENONET ; 
 int EPERM ; 
 scalar_t__ RES_ANY_BUSY ; 
 struct res_common* find_res (struct mlx4_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_tlock (struct mlx4_dev*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_res(struct mlx4_dev *dev, int slave, u64 res_id,
		   enum mlx4_resource type,
		   void *res)
{
	struct res_common *r;
	int err = 0;

	spin_lock_irq(mlx4_tlock(dev));
	r = find_res(dev, res_id, type);
	if (!r) {
		err = -ENONET;
		goto exit;
	}

	if (r->state == RES_ANY_BUSY) {
		err = -EBUSY;
		goto exit;
	}

	if (r->owner != slave) {
		err = -EPERM;
		goto exit;
	}

	r->from_state = r->state;
	r->state = RES_ANY_BUSY;

	if (res)
		*((struct res_common **)res) = r;

exit:
	spin_unlock_irq(mlx4_tlock(dev));
	return err;
}