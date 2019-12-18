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
typedef  int /*<<< orphan*/  taskq_ent_t ;

/* Variables and functions */
 int /*<<< orphan*/  minclsyspri ; 
 int /*<<< orphan*/  mp_ncpus ; 
 int /*<<< orphan*/  system_taskq ; 
 int /*<<< orphan*/  taskq_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_zone ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
system_taskq_init(void *arg)
{

	taskq_zone = uma_zcreate("taskq_zone", sizeof(taskq_ent_t),
	    NULL, NULL, NULL, NULL, 0, 0);
	system_taskq = taskq_create("system_taskq", mp_ncpus, minclsyspri,
	    0, 0, 0);
}