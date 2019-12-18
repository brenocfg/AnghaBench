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
struct grouptask {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qgroup_config ; 
 int /*<<< orphan*/  taskqgroup_detach (int /*<<< orphan*/ ,struct grouptask*) ; 

void
taskqgroup_config_gtask_deinit(struct grouptask *gtask)
{

	taskqgroup_detach(qgroup_config, gtask);
}