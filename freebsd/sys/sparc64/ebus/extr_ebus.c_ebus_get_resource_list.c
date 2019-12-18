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
struct ebus_devinfo {struct resource_list edi_rl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ebus_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource_list *
ebus_get_resource_list(device_t dev, device_t child)
{
	struct ebus_devinfo *edi;

	edi = device_get_ivars(child);
	return (&edi->edi_rl);
}