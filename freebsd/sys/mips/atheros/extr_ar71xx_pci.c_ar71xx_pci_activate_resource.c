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
 int BUS_ACTIVATE_RESOURCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct resource*) ; 
#define  SYS_RES_IOPORT 129 
#define  SYS_RES_MEMORY 128 
 int /*<<< orphan*/  ar71xx_bus_space_pcimem ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_set_bustag (struct resource*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar71xx_pci_activate_resource(device_t bus, device_t child, int type, int rid,
    struct resource *r)
{
	int res = (BUS_ACTIVATE_RESOURCE(device_get_parent(bus),
	    child, type, rid, r));

	if (!res) {
		switch(type) {
		case SYS_RES_MEMORY:
		case SYS_RES_IOPORT:
			rman_set_bustag(r, ar71xx_bus_space_pcimem);
			break;
		}
	}
	return (res);
}