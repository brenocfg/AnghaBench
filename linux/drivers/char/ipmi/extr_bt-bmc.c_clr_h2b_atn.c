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
struct bt_bmc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CTRL ; 
 int /*<<< orphan*/  BT_CTRL_H2B_ATN ; 
 int /*<<< orphan*/  bt_outb (struct bt_bmc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clr_h2b_atn(struct bt_bmc *bt_bmc)
{
	bt_outb(bt_bmc, BT_CTRL_H2B_ATN, BT_CTRL);
}