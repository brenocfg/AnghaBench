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
 int /*<<< orphan*/  addr_wq ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_addr_unregister_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  self ; 

void addr_cleanup(void)
{
	rdma_addr_unregister_client(&self);
	destroy_workqueue(addr_wq);
}