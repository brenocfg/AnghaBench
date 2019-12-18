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
struct uio {TYPE_1__* uio_iov; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  copystr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  dev2udev (struct cdev*) ; 
 scalar_t__ len ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,struct uio*,int) ; 

int
mydev_read(struct cdev *dev, struct uio *uio, int ioflag)
{
    int err = 0;

    printf("mydev_read: dev_t=%lu, uio=%p, ioflag=%d\n",
	dev2udev(dev), uio, ioflag);

    if (len <= 0) {
	err = -1;
    } else {	/* copy buf to userland */
	copystr(&buf, uio->uio_iov->iov_base, 513, &len);
    }
    return(err);
}