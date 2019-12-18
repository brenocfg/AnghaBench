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
struct si_sm_data {TYPE_1__* io; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_BMC_HWRST ; 
 int BT_CLR_WR_PTR ; 
 int /*<<< orphan*/  BT_CONTROL (int) ; 
 int BT_H_BUSY ; 
 int /*<<< orphan*/  BT_INTMASK_W (int /*<<< orphan*/ ) ; 
 int BT_SMS_ATN ; 
 int BT_STATUS ; 
 scalar_t__ bt_debug ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status2txt (int) ; 

__attribute__((used)) static void reset_flags(struct si_sm_data *bt)
{
	if (bt_debug)
		dev_dbg(bt->io->dev, "flag reset %s\n", status2txt(BT_STATUS));
	if (BT_STATUS & BT_H_BUSY)
		BT_CONTROL(BT_H_BUSY);	/* force clear */
	BT_CONTROL(BT_CLR_WR_PTR);	/* always reset */
	BT_CONTROL(BT_SMS_ATN);		/* always clear */
	BT_INTMASK_W(BT_BMC_HWRST);
}