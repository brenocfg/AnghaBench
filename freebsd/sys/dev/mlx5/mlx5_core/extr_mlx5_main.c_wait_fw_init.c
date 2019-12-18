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
typedef  scalar_t__ u32 ;
struct mlx5_core_dev {TYPE_1__* iseg; } ;
struct TYPE_2__ {int /*<<< orphan*/  initializing; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  FW_INIT_WAIT_MS ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int fw_initializing (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int jiffies ; 
 int jiffies_to_msecs (int) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,unsigned int) ; 
 int msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int,int) ; 

__attribute__((used)) static int wait_fw_init(struct mlx5_core_dev *dev, u32 max_wait_mili,
			u32 warn_time_mili)
{
	int warn = jiffies + msecs_to_jiffies(warn_time_mili);
	int end = jiffies + msecs_to_jiffies(max_wait_mili);
	int err = 0;

	MPASS(max_wait_mili > warn_time_mili);

	while (fw_initializing(dev) == 1) {
		if (time_after(jiffies, end)) {
			err = -EBUSY;
			break;
		}
		if (warn_time_mili && time_after(jiffies, warn)) {
			mlx5_core_warn(dev,
			    "Waiting for FW initialization, timeout abort in %u s\n",
			    (unsigned int)(jiffies_to_msecs(end - warn) / 1000));
			warn = jiffies + msecs_to_jiffies(warn_time_mili);
		}
		msleep(FW_INIT_WAIT_MS);
	}

	if (err != 0)
		mlx5_core_dbg(dev, "Full initializing bit dword = 0x%x\n",
		    ioread32be(&dev->iseg->initializing));

	return err;
}