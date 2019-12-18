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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_DEACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
#define  SYS_RES_IOPORT 130 
#define  SYS_RES_IRQ 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int rman_deactivate_resource (struct resource*) ; 

__attribute__((used)) static int
generic_pcie_deactivate_resource(device_t dev, device_t child, int type,
    int rid, struct resource *r)
{
	int res;

	if ((res = rman_deactivate_resource(r)) != 0)
		return (res);

	switch (type) {
	case SYS_RES_IOPORT:
	case SYS_RES_MEMORY:
	case SYS_RES_IRQ:
		res = BUS_DEACTIVATE_RESOURCE(device_get_parent(dev), child,
		    type, rid, r);
		break;
	default:
		break;
	}

	return (res);
}