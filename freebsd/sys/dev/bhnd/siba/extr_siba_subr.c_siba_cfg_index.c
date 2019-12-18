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
typedef  scalar_t__ u_int ;
struct siba_core_id {scalar_t__ num_cfg_blocks; } ;
typedef  scalar_t__ bhnd_port_type ;

/* Variables and functions */
 scalar_t__ BHND_PORT_AGENT ; 
 int ENOENT ; 
 scalar_t__ SIBA_MAX_CFG ; 
 int /*<<< orphan*/  siba_is_port_valid (struct siba_core_id*,scalar_t__,scalar_t__) ; 

int
siba_cfg_index(struct siba_core_id *core_id, bhnd_port_type port_type,
    u_int port, u_int region, u_int *cfgidx)
{
	/* Config blocks are mapped to agent ports */
	if (port_type != BHND_PORT_AGENT)
		return (ENOENT);

	/* Port must be valid */
	if (!siba_is_port_valid(core_id, port_type, port))
		return (ENOENT);

	if (region >= core_id->num_cfg_blocks)
		return (ENOENT);

	if (region >= SIBA_MAX_CFG)
		return (ENOENT);

	/* Found */
	*cfgidx = region;
	return (0);
}