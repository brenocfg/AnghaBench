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
struct TYPE_5__ {TYPE_1__* sw; scalar_t__ dropped; } ;
typedef  TYPE_2__ vertex_t ;
typedef  size_t uint32_t ;
struct TYPE_4__ {scalar_t__ num_of_mcm; scalar_t__ is_mc_member; } ;

/* Variables and functions */

__attribute__((used)) static void reset_mgrp_membership(vertex_t * adj_list, uint32_t adj_list_size)
{
	uint32_t i = 0;

	for (i = 1; i < adj_list_size; i++) {
		if (adj_list[i].dropped)
			continue;

		adj_list[i].sw->is_mc_member = 0;
		adj_list[i].sw->num_of_mcm = 0;
	}
}