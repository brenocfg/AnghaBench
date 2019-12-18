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
struct TYPE_2__ {int /*<<< orphan*/ * parent; int /*<<< orphan*/ * bus; } ;
struct gio_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  gio_bus ; 
 int /*<<< orphan*/  gio_bus_type ; 

int gio_device_register(struct gio_device *giodev)
{
	giodev->dev.bus = &gio_bus_type;
	giodev->dev.parent = &gio_bus;
	return device_register(&giodev->dev);
}