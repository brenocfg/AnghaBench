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
struct nexus_device {struct resource_list nx_resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct nexus_device* DEVTONX (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct resource_list *
nexus_get_reslist(device_t dev, device_t child)
{
	struct nexus_device *ndev = DEVTONX(child);

	return (&ndev->nx_resources);
}