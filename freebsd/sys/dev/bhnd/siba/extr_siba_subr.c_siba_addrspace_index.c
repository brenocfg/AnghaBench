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
typedef  int u_int ;
struct siba_core_id {int num_admatch; } ;
typedef  scalar_t__ bhnd_port_type ;

/* Variables and functions */
 scalar_t__ BHND_PORT_DEVICE ; 
 int ENOENT ; 
 int /*<<< orphan*/  siba_is_port_valid (struct siba_core_id*,scalar_t__,int) ; 

int
siba_addrspace_index(struct siba_core_id *core_id, bhnd_port_type port_type,
    u_int port, u_int region, u_int *addridx)
{
	u_int idx;

	/* Address spaces are always device ports */
	if (port_type != BHND_PORT_DEVICE)
		return (ENOENT);

	/* Port must be valid */
	if (!siba_is_port_valid(core_id, port_type, port))
		return (ENOENT);
	
	if (port == 0)
		idx = region;
	else if (port == 1)
		idx = region + 1;
	else
		return (ENOENT);

	if (idx >= core_id->num_admatch)
		return (ENOENT);

	/* Found */
	*addridx = idx;
	return (0);
}