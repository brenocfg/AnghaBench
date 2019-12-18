#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * p_physp; } ;
typedef  TYPE_1__ osm_qos_port_t ;
typedef  int /*<<< orphan*/  osm_physp_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 

osm_qos_port_t *osm_qos_policy_port_create(osm_physp_t *p_physp)
{
	osm_qos_port_t *p =
	    (osm_qos_port_t *) calloc(1, sizeof(osm_qos_port_t));
	if (p)
		p->p_physp = p_physp;
	return p;
}