#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ id; } ;
union md_node_info {TYPE_1__ ds_port; } ;

/* Variables and functions */

__attribute__((used)) static bool ds_port_node_match(union md_node_info *a_node_info,
			       union md_node_info *b_node_info)
{
	if (a_node_info->ds_port.id != b_node_info->ds_port.id)
		return false;

	return true;
}