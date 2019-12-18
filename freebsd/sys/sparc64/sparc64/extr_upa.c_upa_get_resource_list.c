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
struct upa_devinfo {struct resource_list udi_rl; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct upa_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource_list *
upa_get_resource_list(device_t dev, device_t child)
{
	struct upa_devinfo *udi;

	udi = device_get_ivars(child);
	return (&udi->udi_rl);
}