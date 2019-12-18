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
struct vmci_subscription {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_subscription*) ; 
 int /*<<< orphan*/  subscriber_lock ; 
 int /*<<< orphan*/  vmci_event_release (struct vmci_subscription*) ; 
 int /*<<< orphan*/  vmci_grab_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_release_lock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
event_release_cb(void *client_data)
{
	struct vmci_subscription *sub = (struct vmci_subscription *)client_data;

	ASSERT(sub);

	vmci_grab_lock_bh(&subscriber_lock);
	vmci_event_release(sub);
	vmci_release_lock_bh(&subscriber_lock);

	return (0);
}