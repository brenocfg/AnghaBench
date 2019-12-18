#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_5__ {size_t num_admatch; size_t num_cfg_blocks; } ;
struct siba_devinfo {TYPE_3__* cfg; TYPE_2__ core_id; TYPE_1__* addrspace; } ;
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/  bhnd_port_type ;
struct TYPE_6__ {int cb_rid; } ;
struct TYPE_4__ {int sa_rid; } ;

/* Variables and functions */
 int BHND_BUS_DECODE_PORT_RID (scalar_t__,scalar_t__,int,int,int /*<<< orphan*/ *,size_t*,size_t*) ; 
 int /*<<< orphan*/  BHND_PORT_AGENT ; 
 int /*<<< orphan*/  BHND_PORT_DEVICE ; 
 int EINVAL ; 
 int ENOENT ; 
 int SYS_RES_MEMORY ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 size_t siba_addrspace_device_port (size_t) ; 
 size_t siba_addrspace_device_region (size_t) ; 
 size_t siba_cfg_agent_port (size_t) ; 
 size_t siba_cfg_agent_region (size_t) ; 

__attribute__((used)) static int
siba_decode_port_rid(device_t dev, device_t child, int type, int rid,
    bhnd_port_type *port_type, u_int *port_num, u_int *region_num)
{
	struct siba_devinfo	*dinfo;

	/* delegate non-bus-attached devices to our parent */
	if (device_get_parent(child) != dev)
		return (BHND_BUS_DECODE_PORT_RID(device_get_parent(dev), child,
		    type, rid, port_type, port_num, region_num));

	dinfo = device_get_ivars(child);

	/* Ports are always memory mapped */
	if (type != SYS_RES_MEMORY)
		return (EINVAL);

	/* Look for a matching addrspace entry */
	for (u_int i = 0; i < dinfo->core_id.num_admatch; i++) {
		if (dinfo->addrspace[i].sa_rid != rid)
			continue;

		*port_type = BHND_PORT_DEVICE;
		*port_num = siba_addrspace_device_port(i);
		*region_num = siba_addrspace_device_region(i);
		return (0);
	}

	/* Try the config blocks */
	for (u_int i = 0; i < dinfo->core_id.num_cfg_blocks; i++) {
		if (dinfo->cfg[i].cb_rid != rid)
			continue;

		*port_type = BHND_PORT_AGENT;
		*port_num = siba_cfg_agent_port(i);
		*region_num = siba_cfg_agent_region(i);
		return (0);
	}

	/* Not found */
	return (ENOENT);
}