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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MAKEDEV_ETERNAL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  evtchn_devsw ; 
 int /*<<< orphan*/  make_dev_credf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int
evtchn_attach(device_t dev)
{

	make_dev_credf(MAKEDEV_ETERNAL, &evtchn_devsw, 0, NULL, UID_ROOT,
	    GID_WHEEL, 0600, "xen/evtchn");
	return (0);
}