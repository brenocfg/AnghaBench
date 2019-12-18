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
struct vmci_doorbell_entry {int /*<<< orphan*/  destroy_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct vmci_doorbell_entry*) ; 
 int /*<<< orphan*/  vmci_signal_event (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vmci_doorbell_free_cb(void *client_data)
{
	struct vmci_doorbell_entry *entry;

	entry = (struct vmci_doorbell_entry *)client_data;
	ASSERT(entry);
	vmci_signal_event(&entry->destroy_event);
}