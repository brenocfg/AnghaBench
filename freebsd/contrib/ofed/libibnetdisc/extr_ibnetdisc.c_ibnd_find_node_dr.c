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
struct TYPE_3__ {int /*<<< orphan*/ * node; } ;
typedef  TYPE_1__ ibnd_port_t ;
typedef  int /*<<< orphan*/  ibnd_node_t ;
typedef  int /*<<< orphan*/  ibnd_fabric_t ;

/* Variables and functions */
 TYPE_1__* ibnd_find_port_dr (int /*<<< orphan*/ *,char*) ; 

ibnd_node_t *ibnd_find_node_dr(ibnd_fabric_t * fabric, char *dr_str)
{
	ibnd_port_t *rc = ibnd_find_port_dr(fabric, dr_str);
	return rc->node;
}