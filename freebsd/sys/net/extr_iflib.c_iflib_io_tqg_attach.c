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
 int /*<<< orphan*/  qgroup_if_io_tqg ; 
 int /*<<< orphan*/  taskqgroup_attach_cpu (int /*<<< orphan*/ ,struct grouptask*,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 

void
iflib_io_tqg_attach(struct grouptask *gt, void *uniq, int cpu, const char *name)
{

	taskqgroup_attach_cpu(qgroup_if_io_tqg, gt, uniq, cpu, NULL, NULL,
	    name);
}