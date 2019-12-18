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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
struct siba_devinfo {int /*<<< orphan*/  resources; struct siba_addrspace* addrspace; } ;
struct siba_addrspace {int sa_base; int sa_size; int sa_bus_reserved; int /*<<< orphan*/  sa_rid; } ;
typedef  int rman_res_t ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int UINT32_MAX ; 
 size_t nitems (struct siba_addrspace*) ; 
 int /*<<< orphan*/  resource_list_add_next (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int
siba_append_dinfo_region(struct siba_devinfo *dinfo, uint8_t addridx,
    uint32_t base, uint32_t size, uint32_t bus_reserved)
{
	struct siba_addrspace	*sa;
	rman_res_t		 r_size;

	/* Verify that base + size will not overflow */
	if (size > 0 && UINT32_MAX - (size - 1) < base)
		return (ERANGE);

	/* Verify that size - bus_reserved will not underflow */
	if (size < bus_reserved)
		return (ERANGE);

	/* Must not be 0-length */
	if (size == 0)
		return (EINVAL);

	/* Must not exceed addrspace array size */
	if (addridx >= nitems(dinfo->addrspace))
		return (EINVAL);

	/* Initialize new addrspace entry */
	sa = &dinfo->addrspace[addridx];
	sa->sa_base = base;
	sa->sa_size = size;
	sa->sa_bus_reserved = bus_reserved;

	/* Populate the resource list */
	r_size = size - bus_reserved;
	sa->sa_rid = resource_list_add_next(&dinfo->resources, SYS_RES_MEMORY,
	    base, base + (r_size - 1), r_size);

	return (0);
}