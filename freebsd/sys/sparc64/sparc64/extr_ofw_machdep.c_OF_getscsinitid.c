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
typedef  int uint32_t ;
typedef  int u_int ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  id ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ OF_getprop (scalar_t__,char*,int*,int) ; 
 scalar_t__ OF_parent (scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 

u_int
OF_getscsinitid(device_t dev)
{
	phandle_t node;
	uint32_t id;

	for (node = ofw_bus_get_node(dev); node != 0; node = OF_parent(node))
		if (OF_getprop(node, "scsi-initiator-id", &id,
		    sizeof(id)) > 0)
			return (id);
	return (7);
}