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
struct switch_dev {int dummy; } ;

/* Variables and functions */
 int mvsw61xx_update_state (struct switch_dev*) ; 

__attribute__((used)) static int mvsw61xx_apply(struct switch_dev *dev)
{
	return mvsw61xx_update_state(dev);
}