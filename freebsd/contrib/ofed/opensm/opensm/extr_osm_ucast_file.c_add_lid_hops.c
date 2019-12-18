#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {unsigned int num_ports; } ;
typedef  TYPE_1__ osm_switch_t ;
typedef  int /*<<< orphan*/  osm_opensm_t ;
typedef  int /*<<< orphan*/  ib_net64_t ;

/* Variables and functions */
 int /*<<< orphan*/  osm_switch_set_hops (TYPE_1__*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void add_lid_hops(osm_opensm_t * p_osm, osm_switch_t * p_sw,
			 uint16_t lid, ib_net64_t guid,
			 uint8_t hops[], unsigned len)
{
	uint8_t i;

	if (len > p_sw->num_ports)
		len = p_sw->num_ports;

	for (i = 0; i < len; i++)
		osm_switch_set_hops(p_sw, lid, i, hops[i]);
}