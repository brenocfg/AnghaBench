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
struct siba_cfg_block {scalar_t__ cb_size; int /*<<< orphan*/  cb_base; } ;
struct siba_addrspace {scalar_t__ sa_bus_reserved; scalar_t__ sa_size; int /*<<< orphan*/  sa_base; } ;
typedef  scalar_t__ device_t ;
typedef  scalar_t__ bhnd_size_t ;
typedef  int /*<<< orphan*/  bhnd_port_type ;
typedef  int /*<<< orphan*/  bhnd_addr_t ;

/* Variables and functions */
 int BHND_BUS_GET_REGION_ADDR (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int ENOENT ; 
 struct siba_devinfo* device_get_ivars (scalar_t__) ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct siba_addrspace* siba_find_addrspace (struct siba_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct siba_cfg_block* siba_find_cfg_block (struct siba_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
siba_get_region_addr(device_t dev, device_t child, bhnd_port_type port_type,
    u_int port_num, u_int region_num, bhnd_addr_t *addr, bhnd_size_t *size)
{
	struct siba_devinfo	*dinfo;
	struct siba_addrspace	*addrspace;
	struct siba_cfg_block	*cfg;

	/* delegate non-bus-attached devices to our parent */
	if (device_get_parent(child) != dev) {
		return (BHND_BUS_GET_REGION_ADDR(device_get_parent(dev), child,
		    port_type, port_num, region_num, addr, size));
	}

	dinfo = device_get_ivars(child);

	/* Look for a matching addrspace */
	addrspace = siba_find_addrspace(dinfo, port_type, port_num, region_num);
	if (addrspace != NULL) {
		*addr = addrspace->sa_base;
		*size = addrspace->sa_size - addrspace->sa_bus_reserved;
		return (0);
	}

	/* Look for a matching cfg block */
	cfg = siba_find_cfg_block(dinfo, port_type, port_num, region_num);
	if (cfg != NULL) {
		*addr = cfg->cb_base;
		*size = cfg->cb_size;
		return (0);
	}

	/* Not found */
	return (ENOENT);
}