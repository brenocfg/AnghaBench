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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  hcr_mutex; } ;
struct mthca_dev {TYPE_1__ cmd; } ;

/* Variables and functions */
 int MTHCA_CMD_POST_DOORBELLS ; 
 scalar_t__ fw_cmd_doorbell ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  mthca_cmd_post_dbell (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mthca_cmd_post_hcr (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mthca_cmd_post(struct mthca_dev *dev,
			  u64 in_param,
			  u64 out_param,
			  u32 in_modifier,
			  u8 op_modifier,
			  u16 op,
			  u16 token,
			  int event)
{
	int err = 0;

	mutex_lock(&dev->cmd.hcr_mutex);

	if (event && dev->cmd.flags & MTHCA_CMD_POST_DOORBELLS && fw_cmd_doorbell)
		mthca_cmd_post_dbell(dev, in_param, out_param, in_modifier,
					   op_modifier, op, token);
	else
		err = mthca_cmd_post_hcr(dev, in_param, out_param, in_modifier,
					 op_modifier, op, token, event);

	/*
	 * Make sure that our HCR writes don't get mixed in with
	 * writes from another CPU starting a FW command.
	 */
	mmiowb();

	mutex_unlock(&dev->cmd.hcr_mutex);
	return err;
}