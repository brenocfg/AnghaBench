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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct res_qp {int /*<<< orphan*/  mcg_spl; } ;
struct res_gid {int prot; int steer; int /*<<< orphan*/  list; int /*<<< orphan*/  reg_id; } ;
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_steer_type { ____Placeholder_mlx4_steer_type } mlx4_steer_type ;
typedef  enum mlx4_protocol { ____Placeholder_mlx4_protocol } mlx4_protocol ;

/* Variables and functions */
 int EINVAL ; 
 struct res_gid* find_gid (struct mlx4_dev*,int,struct res_qp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct res_gid*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rem_mcg_res(struct mlx4_dev *dev, int slave, struct res_qp *rqp,
		       u8 *gid, enum mlx4_protocol prot,
		       enum mlx4_steer_type steer, u64 *reg_id)
{
	struct res_gid *res;
	int err;

	spin_lock_irq(&rqp->mcg_spl);
	res = find_gid(dev, slave, rqp, gid);
	if (!res || res->prot != prot || res->steer != steer)
		err = -EINVAL;
	else {
		*reg_id = res->reg_id;
		list_del(&res->list);
		kfree(res);
		err = 0;
	}
	spin_unlock_irq(&rqp->mcg_spl);

	return err;
}