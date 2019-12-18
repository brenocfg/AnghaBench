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
 int /*<<< orphan*/  bulk_waiter_spinlock ; 
 int /*<<< orphan*/  quota_spinlock ; 
 int /*<<< orphan*/  service_spinlock ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void
vchiq_core_initialize(void)
{
	spin_lock_init(&service_spinlock);
	spin_lock_init(&bulk_waiter_spinlock);
	spin_lock_init(&quota_spinlock);
}