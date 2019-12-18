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
struct siba_core_id {int /*<<< orphan*/  num_cfg_blocks; int /*<<< orphan*/  num_admatch; } ;
typedef  int bhnd_port_type ;

/* Variables and functions */
#define  BHND_PORT_AGENT 129 
#define  BHND_PORT_DEVICE 128 
 int min (int /*<<< orphan*/ ,int) ; 

u_int
siba_port_count(struct siba_core_id *core_id, bhnd_port_type port_type)
{
	switch (port_type) {
	case BHND_PORT_DEVICE:
		/* 0, 1, or 2 ports */
		return (min(core_id->num_admatch, 2));

	case BHND_PORT_AGENT:
		/* One agent port maps all configuration blocks */
		if (core_id->num_cfg_blocks > 0)
			return (1);

		/* Do not advertise an agent port if there are no configuration
		 * register blocks */
		return (0);

	default:
		return (0);
	}
}