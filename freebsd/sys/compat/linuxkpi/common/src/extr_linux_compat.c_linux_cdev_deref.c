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
struct linux_cdev {int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct linux_cdev*) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
linux_cdev_deref(struct linux_cdev *ldev)
{

	if (refcount_release(&ldev->refs))
		kfree(ldev);
}