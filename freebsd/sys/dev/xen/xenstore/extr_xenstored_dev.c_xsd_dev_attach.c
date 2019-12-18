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
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 struct cdev* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  xsd_dev_cdevsw ; 

__attribute__((used)) static int
xsd_dev_attach(device_t dev)
{
	struct cdev *xsd_cdev;

	xsd_cdev = make_dev(&xsd_dev_cdevsw, 0, UID_ROOT, GID_WHEEL, 0400,
	    "xen/xenstored");
	if (xsd_cdev == NULL)
		return (EINVAL);

	return (0);
}