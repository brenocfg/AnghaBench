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
struct make_dev_args {int mda_flags; int mda_mode; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_devsw; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_OPERATOR ; 
 int MAKEDEV_CHECKNAME ; 
 int MAKEDEV_WAITOK ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 int make_dev_s (struct make_dev_args*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mlx5_ctl_dev ; 
 int /*<<< orphan*/  mlx5_ctl_devsw ; 

int
mlx5_ctl_init(void)
{
	struct make_dev_args mda;
	int error;

	make_dev_args_init(&mda);
	mda.mda_flags = MAKEDEV_WAITOK | MAKEDEV_CHECKNAME;
	mda.mda_devsw = &mlx5_ctl_devsw;
	mda.mda_uid = UID_ROOT;
	mda.mda_gid = GID_OPERATOR;
	mda.mda_mode = 0640;
	error = make_dev_s(&mda, &mlx5_ctl_dev, "mlx5ctl");
	return (-error);
}