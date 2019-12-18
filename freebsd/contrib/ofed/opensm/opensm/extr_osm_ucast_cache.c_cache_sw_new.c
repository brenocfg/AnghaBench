#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {unsigned int num_ports; TYPE_1__* ports; } ;
typedef  TYPE_2__ cache_switch_t ;
typedef  int /*<<< orphan*/  cache_port_t ;
struct TYPE_6__ {int /*<<< orphan*/  is_leaf; int /*<<< orphan*/  remote_lid_ho; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static cache_switch_t *cache_sw_new(uint16_t lid_ho, unsigned num_ports)
{
	cache_switch_t *p_cache_sw = malloc(sizeof(cache_switch_t) +
					    num_ports * sizeof(cache_port_t));
	if (!p_cache_sw)
		return NULL;

	memset(p_cache_sw, 0,
	       sizeof(*p_cache_sw) + num_ports * sizeof(cache_port_t));

	p_cache_sw->num_ports = num_ports;

	/* port[0] fields represent this switch details - lid and type */
	p_cache_sw->ports[0].remote_lid_ho = lid_ho;
	p_cache_sw->ports[0].is_leaf = FALSE;

	return p_cache_sw;
}