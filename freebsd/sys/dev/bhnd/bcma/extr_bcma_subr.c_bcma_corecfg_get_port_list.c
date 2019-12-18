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
struct bcma_sport_list {int dummy; } ;
struct bcma_corecfg {struct bcma_sport_list wrapper_ports; struct bcma_sport_list bridge_ports; struct bcma_sport_list dev_ports; } ;
typedef  int bhnd_port_type ;

/* Variables and functions */
#define  BHND_PORT_AGENT 130 
#define  BHND_PORT_BRIDGE 129 
#define  BHND_PORT_DEVICE 128 

struct bcma_sport_list *
bcma_corecfg_get_port_list(struct bcma_corecfg *cfg, bhnd_port_type type)
{
	switch (type) {
	case BHND_PORT_DEVICE:
		return (&cfg->dev_ports);
		break;
	case BHND_PORT_BRIDGE:
		return (&cfg->bridge_ports);
		break;
	case BHND_PORT_AGENT:
		return (&cfg->wrapper_ports);
		break;
	default:
		return (NULL);
	}
}