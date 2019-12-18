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
struct moxtet_device {scalar_t__ idx; struct moxtet* moxtet; } ;
struct moxtet {scalar_t__ count; int /*<<< orphan*/  lock; int /*<<< orphan*/ * tx; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int spi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 struct moxtet_device* to_moxtet_device (struct device*) ; 
 int /*<<< orphan*/  to_spi_device (int /*<<< orphan*/ ) ; 

int moxtet_device_write(struct device *dev, u8 val)
{
	struct moxtet_device *mdev = to_moxtet_device(dev);
	struct moxtet *moxtet = mdev->moxtet;
	int ret;

	if (mdev->idx >= moxtet->count)
		return -EINVAL;

	mutex_lock(&moxtet->lock);

	moxtet->tx[moxtet->count - mdev->idx] = val;

	ret = spi_write(to_spi_device(moxtet->dev), moxtet->tx,
			moxtet->count + 1);

	mutex_unlock(&moxtet->lock);

	return ret;
}