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
 int /*<<< orphan*/  CMD_SW2HW_MPT ; 
 int /*<<< orphan*/  CMD_TIME_CLASS_B ; 
 int mthca_cmd (struct mthca_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mthca_SW2HW_MPT(struct mthca_dev *dev, struct mthca_mailbox *mailbox,
		    int mpt_index)
{
	return mthca_cmd(dev, mailbox->dma, mpt_index, 0, CMD_SW2HW_MPT,
			 CMD_TIME_CLASS_B);
}