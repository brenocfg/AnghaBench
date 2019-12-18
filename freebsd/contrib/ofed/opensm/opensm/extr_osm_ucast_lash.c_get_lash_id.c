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
struct TYPE_4__ {int id; } ;
typedef  TYPE_1__ switch_t ;
struct TYPE_5__ {scalar_t__ priv; } ;
typedef  TYPE_2__ osm_switch_t ;

/* Variables and functions */

__attribute__((used)) static unsigned get_lash_id(osm_switch_t * p_sw)
{
	return ((switch_t *) p_sw->priv)->id;
}