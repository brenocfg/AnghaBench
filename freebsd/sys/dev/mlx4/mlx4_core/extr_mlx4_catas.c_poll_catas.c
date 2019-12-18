#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  timer; int /*<<< orphan*/ * map; } ;
struct TYPE_6__ {TYPE_1__* comm; } ;
struct mlx4_priv {TYPE_3__ catas_err; TYPE_2__ mfunc; } ;
struct mlx4_dev {TYPE_4__* persist; } ;
struct TYPE_8__ {int state; int /*<<< orphan*/  catas_work; int /*<<< orphan*/  catas_wq; } ;
struct TYPE_5__ {int /*<<< orphan*/  slave_read; } ;

/* Variables and functions */
 scalar_t__ MLX4_CATAS_POLL_INTERVAL ; 
 int MLX4_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  dump_err_buf (struct mlx4_dev*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ mlx4_comm_internal_err (int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_internal_err_reset ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  swab32 (scalar_t__) ; 

__attribute__((used)) static void poll_catas(unsigned long dev_ptr)
{
	struct mlx4_dev *dev = (struct mlx4_dev *) dev_ptr;
	struct mlx4_priv *priv = mlx4_priv(dev);
	u32 slave_read;

	if (mlx4_is_slave(dev)) {
		slave_read = swab32(readl(&priv->mfunc.comm->slave_read));
		if (mlx4_comm_internal_err(slave_read)) {
			mlx4_warn(dev, "Internal error detected on the communication channel\n");
			goto internal_err;
		}
	} else if (readl(priv->catas_err.map)) {
		dump_err_buf(dev);
		goto internal_err;
	}

	if (dev->persist->state & MLX4_DEVICE_STATE_INTERNAL_ERROR) {
		mlx4_warn(dev, "Internal error mark was detected on device\n");
		goto internal_err;
	}

	mod_timer(&priv->catas_err.timer,
		  round_jiffies(jiffies + MLX4_CATAS_POLL_INTERVAL));
	return;

internal_err:
	if (mlx4_internal_err_reset)
		queue_work(dev->persist->catas_wq, &dev->persist->catas_work);
}