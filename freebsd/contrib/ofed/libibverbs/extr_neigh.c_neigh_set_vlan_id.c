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
typedef  int uint16_t ;
struct get_neigh_handler {int vid; } ;

/* Variables and functions */

void neigh_set_vlan_id(struct get_neigh_handler *neigh_handler, uint16_t vid)
{
	if (vid <= 0xfff)
		neigh_handler->vid = vid;
}