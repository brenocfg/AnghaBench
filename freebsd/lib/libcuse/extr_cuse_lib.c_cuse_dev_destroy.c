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
struct cuse_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUSE_IOCTL_DESTROY_DEV ; 
 int /*<<< orphan*/  CUSE_LOCK () ; 
 int /*<<< orphan*/  CUSE_UNLOCK () ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cuse_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 scalar_t__ f_cuse ; 
 int /*<<< orphan*/  free (struct cuse_dev*) ; 
 int /*<<< orphan*/  h_cuse ; 
 int ioctl (scalar_t__,int /*<<< orphan*/ ,struct cuse_dev**) ; 

void
cuse_dev_destroy(struct cuse_dev *cdev)
{
	int error;

	if (f_cuse < 0)
		return;

	CUSE_LOCK();
	TAILQ_REMOVE(&h_cuse, cdev, entry);
	CUSE_UNLOCK();

	error = ioctl(f_cuse, CUSE_IOCTL_DESTROY_DEV, &cdev);
	if (error)
		return;

	free(cdev);
}