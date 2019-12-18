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
 int copyinstr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev2udev (struct cdev*) ; 
 int /*<<< orphan*/  len ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
mydev_write(struct cdev *dev, struct uio *uio, int ioflag)
{
    int err = 0;

    printf("mydev_write: dev_t=%lu, uio=%p, ioflag=%d\n",
	dev2udev(dev), uio, ioflag);

    err = copyinstr(uio->uio_iov->iov_base, &buf, 512, &len);
    if (err != 0) {
	printf("Write to \"cdev\" failed.\n");
    }
    return(err);
}