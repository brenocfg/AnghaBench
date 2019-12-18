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
struct isa_device {struct resource_list id_resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct isa_device* DEVTOISA (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource_list *
isa_get_resource_list (device_t dev, device_t child)
{
	struct isa_device* idev = DEVTOISA(child);
	struct resource_list *rl = &idev->id_resources;

	if (!rl)
		return (NULL);

	return (rl);
}