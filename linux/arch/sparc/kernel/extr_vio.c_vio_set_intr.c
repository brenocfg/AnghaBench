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

/* Variables and functions */
 int /*<<< orphan*/  cdev_cfg_handle ; 
 int sun4v_vintr_set_valid (int /*<<< orphan*/ ,unsigned long,int) ; 

int vio_set_intr(unsigned long dev_ino, int state)
{
	int err;

	err = sun4v_vintr_set_valid(cdev_cfg_handle, dev_ino, state);
	return err;
}