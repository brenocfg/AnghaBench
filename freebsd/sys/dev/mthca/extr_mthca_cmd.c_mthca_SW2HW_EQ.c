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
struct mthca_mailbox {int /*<<< orphan*/  dma; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SW2HW_EQ ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_A ; 
 int mthca_cmd (struct mthca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mthca_SW2HW_EQ(struct mthca_dev *dev, struct mthca_mailbox *mailbox,
		   int eq_num)
{
	return mthca_cmd(dev, mailbox->dma, eq_num, 0, CMD_SW2HW_EQ,
			 CMD_TIME_CLASS_A);
}