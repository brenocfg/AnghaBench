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
typedef  int u8 ;
struct file {int dummy; } ;
struct bt_bmc {int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int /*<<< orphan*/  __poll_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CTRL ; 
 int BT_CTRL_B2H_ATN ; 
 int BT_CTRL_H2B_ATN ; 
 int BT_CTRL_H_BUSY ; 
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLLOUT ; 
 int bt_inb (struct bt_bmc*,int /*<<< orphan*/ ) ; 
 struct bt_bmc* file_bt_bmc (struct file*) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t bt_bmc_poll(struct file *file, poll_table *wait)
{
	struct bt_bmc *bt_bmc = file_bt_bmc(file);
	__poll_t mask = 0;
	u8 ctrl;

	poll_wait(file, &bt_bmc->queue, wait);

	ctrl = bt_inb(bt_bmc, BT_CTRL);

	if (ctrl & BT_CTRL_H2B_ATN)
		mask |= EPOLLIN;

	if (!(ctrl & (BT_CTRL_H_BUSY | BT_CTRL_B2H_ATN)))
		mask |= EPOLLOUT;

	return mask;
}