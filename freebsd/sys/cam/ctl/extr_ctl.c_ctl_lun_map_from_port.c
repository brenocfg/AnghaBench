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
typedef  size_t uint32_t ;
struct ctl_port {size_t* lun_map; size_t lun_map_size; } ;

/* Variables and functions */
 size_t UINT32_MAX ; 

uint32_t
ctl_lun_map_from_port(struct ctl_port *port, uint32_t lun_id)
{

	if (port == NULL)
		return (UINT32_MAX);
	if (port->lun_map == NULL)
		return (lun_id);
	if (lun_id > port->lun_map_size)
		return (UINT32_MAX);
	return (port->lun_map[lun_id]);
}