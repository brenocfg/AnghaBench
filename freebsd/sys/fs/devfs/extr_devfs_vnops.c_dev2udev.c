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
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_2__ {int /*<<< orphan*/  cdp_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NODEV ; 
 TYPE_1__* cdev2priv (struct cdev*) ; 

dev_t
dev2udev(struct cdev *x)
{
	if (x == NULL)
		return (NODEV);
	return (cdev2priv(x)->cdp_inode);
}