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
typedef  size_t u_int ;
struct siba_devinfo {struct siba_addrspace* addrspace; int /*<<< orphan*/  core_id; } ;
struct siba_addrspace {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_port_type ;

/* Variables and functions */
 size_t SIBA_MAX_ADDRSPACE ; 
 int siba_addrspace_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,size_t,size_t*) ; 

struct siba_addrspace *
siba_find_addrspace(struct siba_devinfo *dinfo, bhnd_port_type type, u_int port,
    u_int region)
{
	u_int	addridx;
	int	error;

	/* Map to addrspace index */
	error = siba_addrspace_index(&dinfo->core_id, type, port, region,
	    &addridx);
	if (error)
		return (NULL);

	/* Found */
	if (addridx >= SIBA_MAX_ADDRSPACE)
		return (NULL);

	return (&dinfo->addrspace[addridx]);
}