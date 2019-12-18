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
struct moxtet_device {TYPE_1__* moxtet; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct moxtet_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ ) ; 
 struct moxtet_device* to_moxtet_device (struct device*) ; 

__attribute__((used)) static void moxtet_dev_release(struct device *dev)
{
	struct moxtet_device *mdev = to_moxtet_device(dev);

	put_device(mdev->moxtet->dev);
	kfree(mdev);
}