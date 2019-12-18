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

/* Variables and functions */
 int /*<<< orphan*/  CARP_LOG (char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  V_carp_demotion ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  carp_sendall_task ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static void
carp_demote_adj(int adj, char *reason)
{
	atomic_add_int(&V_carp_demotion, adj);
	CARP_LOG("demoted by %d to %d (%s)\n", adj, V_carp_demotion, reason);
	taskqueue_enqueue(taskqueue_swi, &carp_sendall_task);
}