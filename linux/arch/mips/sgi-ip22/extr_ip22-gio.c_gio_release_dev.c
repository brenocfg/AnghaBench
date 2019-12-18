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
struct gio_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct gio_device*) ; 
 struct gio_device* to_gio_device (struct device*) ; 

void gio_release_dev(struct device *dev)
{
	struct gio_device *giodev;

	giodev = to_gio_device(dev);
	kfree(giodev);
}