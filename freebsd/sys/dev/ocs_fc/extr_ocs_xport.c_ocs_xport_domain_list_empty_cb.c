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
typedef  int /*<<< orphan*/  ocs_t ;
typedef  int /*<<< orphan*/  ocs_sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_sem_v (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ocs_xport_domain_list_empty_cb(ocs_t *ocs, void *arg)
{
	ocs_sem_t *sem = arg;

	ocs_assert(ocs);
	ocs_assert(sem);

	ocs_sem_v(sem);
}