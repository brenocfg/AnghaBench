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
 int ENOMEM ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  addr_wq ; 
 int /*<<< orphan*/  alloc_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_addr_register_client (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  self ; 

int addr_init(void)
{
	addr_wq = alloc_workqueue("ib_addr", WQ_MEM_RECLAIM, 0);
	if (!addr_wq)
		return -ENOMEM;

	rdma_addr_register_client(&self);

	return 0;
}