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
struct vmci_subscription {int /*<<< orphan*/  callback_data; int /*<<< orphan*/  id; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,struct vmci_event_data*,int /*<<< orphan*/ ) ;scalar_t__ event_payload; struct vmci_subscription* sub; } ;
struct vmci_event_data {int dummy; } ;
struct vmci_delayed_event_info {int /*<<< orphan*/  callback_data; int /*<<< orphan*/  id; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,struct vmci_event_data*,int /*<<< orphan*/ ) ;scalar_t__ event_payload; struct vmci_delayed_event_info* sub; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_subscription*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct vmci_event_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subscriber_lock ; 
 int /*<<< orphan*/  vmci_event_release (struct vmci_subscription*) ; 
 int /*<<< orphan*/  vmci_free_kernel_mem (struct vmci_subscription*,int) ; 
 int /*<<< orphan*/  vmci_grab_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_release_lock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vmci_event_delayed_dispatch_cb(void *data)
{
	struct vmci_delayed_event_info *event_info;
	struct vmci_subscription *sub;
	struct vmci_event_data *ed;

	event_info = (struct vmci_delayed_event_info *)data;

	ASSERT(event_info);
	ASSERT(event_info->sub);

	sub = event_info->sub;
	ed = (struct vmci_event_data *)event_info->event_payload;

	sub->callback(sub->id, ed, sub->callback_data);

	vmci_grab_lock_bh(&subscriber_lock);
	vmci_event_release(sub);
	vmci_release_lock_bh(&subscriber_lock);

	vmci_free_kernel_mem(event_info, sizeof(*event_info));
}