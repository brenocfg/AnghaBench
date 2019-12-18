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
struct p2p_group_config {int dummy; } ;
struct p2p_group {struct p2p_group_config const* cfg; } ;

/* Variables and functions */

const struct p2p_group_config * p2p_group_get_config(struct p2p_group *group)
{
	return group->cfg;
}