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
typedef  int /*<<< orphan*/  u8 ;
struct opal_user_lr_setup {int /*<<< orphan*/  WLE; int /*<<< orphan*/  RLE; } ;
struct opal_dev {int dummy; } ;

/* Variables and functions */
 int generic_lr_enable_disable (struct opal_dev*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static inline int enable_global_lr(struct opal_dev *dev, u8 *uid,
				   struct opal_user_lr_setup *setup)
{
	int err;

	err = generic_lr_enable_disable(dev, uid, !!setup->RLE, !!setup->WLE,
					0, 0);
	if (err)
		pr_debug("Failed to create enable global lr command\n");

	return err;
}