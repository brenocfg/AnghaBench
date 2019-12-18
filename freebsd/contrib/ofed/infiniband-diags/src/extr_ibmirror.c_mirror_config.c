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
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  port_mirror_ports (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  port_mirror_route (int /*<<< orphan*/ *,int,int) ; 

int mirror_config(ib_portid_t* portid, int query, int clear)
{
	port_mirror_route(portid, query, clear);
	/* port_mirror_filter(portid, query, clear); */
	port_mirror_ports(portid, query, clear);

	return 0;
}