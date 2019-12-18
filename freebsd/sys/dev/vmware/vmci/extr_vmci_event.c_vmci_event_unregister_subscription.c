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
typedef  int /*<<< orphan*/  vmci_id ;
struct vmci_subscription {int /*<<< orphan*/  destroy_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_release_cb ; 
 int /*<<< orphan*/  subscriber_list_item ; 
 int /*<<< orphan*/  subscriber_lock ; 
 int /*<<< orphan*/  vmci_destroy_event (int /*<<< orphan*/ *) ; 
 struct vmci_subscription* vmci_event_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_event_release (struct vmci_subscription*) ; 
 int /*<<< orphan*/  vmci_grab_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_list_remove (struct vmci_subscription*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmci_release_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmci_wait_on_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct vmci_subscription*) ; 

__attribute__((used)) static struct vmci_subscription *
vmci_event_unregister_subscription(vmci_id sub_id)
{
	struct vmci_subscription *s;

	vmci_grab_lock_bh(&subscriber_lock);
	s = vmci_event_find(sub_id);
	if (s != NULL) {
		vmci_event_release(s);
		vmci_list_remove(s, subscriber_list_item);
	}
	vmci_release_lock_bh(&subscriber_lock);

	if (s != NULL) {
		vmci_wait_on_event(&s->destroy_event, event_release_cb, s);
		vmci_destroy_event(&s->destroy_event);
	}

	return (s);
}