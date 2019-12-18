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
 scalar_t__ STAILQ_FIRST (struct resource_list*) ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 scalar_t__ printf (char*) ; 
 scalar_t__ resource_list_print_type (struct resource_list*,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
nexus_print_all_resources(device_t dev)
{
	struct	nexus_device *ndev = DEVTONX(dev);
	struct resource_list *rl = &ndev->nx_resources;
	int retval = 0;

	if (STAILQ_FIRST(rl))
		retval += printf(" at");

	retval += resource_list_print_type(rl, "port", SYS_RES_IOPORT, "%#jx");
	retval += resource_list_print_type(rl, "iomem", SYS_RES_MEMORY, "%#jx");
	retval += resource_list_print_type(rl, "irq", SYS_RES_IRQ, "%jd");

	return retval;
}