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
struct siba_devinfo {int dummy; } ;
struct siba_cfg_block {int cb_rid; } ;
struct siba_addrspace {int sa_rid; } ;
typedef  scalar_t__ device_t ;
typedef  int /*<<< orphan*/  bhnd_port_type ;

/* Variables and functions */
 int BHND_BUS_GET_PORT_RID (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct siba_addrspace* siba_find_addrspace (struct siba_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct siba_cfg_block* siba_find_cfg_block (struct siba_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siba_get_port_rid(device_t dev, device_t child, bhnd_port_type port_type,
    u_int port_num, u_int region_num)
{
	struct siba_devinfo	*dinfo;
	struct siba_addrspace	*addrspace;
	struct siba_cfg_block	*cfg;

	/* delegate non-bus-attached devices to our parent */
	if (device_get_parent(child) != dev)
		return (BHND_BUS_GET_PORT_RID(device_get_parent(dev), child,
		    port_type, port_num, region_num));

	dinfo = device_get_ivars(child);

	/* Look for a matching addrspace entry */
	addrspace = siba_find_addrspace(dinfo, port_type, port_num, region_num);
	if (addrspace != NULL)
		return (addrspace->sa_rid);

	/* Try the config blocks */
	cfg = siba_find_cfg_block(dinfo, port_type, port_num, region_num);
	if (cfg != NULL)
		return (cfg->cb_rid);

	/* Not found */
	return (-1);
}