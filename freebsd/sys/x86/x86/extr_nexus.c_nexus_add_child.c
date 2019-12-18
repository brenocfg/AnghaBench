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
typedef  int /*<<< orphan*/  u_int ;
struct nexus_device {int /*<<< orphan*/  nx_resources; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_NEXUSDEV ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  device_add_child_ordered (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,struct nexus_device*) ; 
 struct nexus_device* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_list_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static device_t
nexus_add_child(device_t bus, u_int order, const char *name, int unit)
{
	device_t		child;
	struct nexus_device	*ndev;

	ndev = malloc(sizeof(struct nexus_device), M_NEXUSDEV, M_NOWAIT|M_ZERO);
	if (!ndev)
		return(0);
	resource_list_init(&ndev->nx_resources);

	child = device_add_child_ordered(bus, order, name, unit);

	/* should we free this in nexus_child_detached? */
	device_set_ivars(child, ndev);

	return(child);
}