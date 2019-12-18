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
struct resource_list {int dummy; } ;
struct superio_devinfo {struct resource_list resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 struct superio_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 scalar_t__ resource_list_release_active (struct resource_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  superio_printf (struct superio_devinfo*,char*) ; 

__attribute__((used)) static void
superio_child_detached(device_t dev, device_t child)
{
	struct superio_devinfo *dinfo;
	struct resource_list *rl;

	dinfo = device_get_ivars(child);
	rl = &dinfo->resources;

	if (resource_list_release_active(rl, dev, child, SYS_RES_IRQ) != 0)
		superio_printf(dinfo, "Device leaked IRQ resources\n");
	if (resource_list_release_active(rl, dev, child, SYS_RES_MEMORY) != 0)
		superio_printf(dinfo, "Device leaked memory resources\n");
	if (resource_list_release_active(rl, dev, child, SYS_RES_IOPORT) != 0)
		superio_printf(dinfo, "Device leaked I/O resources\n");
}