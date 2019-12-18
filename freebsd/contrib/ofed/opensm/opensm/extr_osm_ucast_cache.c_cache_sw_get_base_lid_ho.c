#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {TYPE_1__* ports; } ;
typedef  TYPE_2__ cache_switch_t ;
struct TYPE_4__ {int /*<<< orphan*/  remote_lid_ho; } ;

/* Variables and functions */

__attribute__((used)) static uint16_t cache_sw_get_base_lid_ho(cache_switch_t * p_sw)
{
	return p_sw->ports[0].remote_lid_ho;
}