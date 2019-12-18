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
struct datagram_entry {int /*<<< orphan*/  destroy_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct datagram_entry*) ; 
 int /*<<< orphan*/  vmci_signal_event (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
datagram_free_cb(void *client_data)
{
	struct datagram_entry *entry = (struct datagram_entry *)client_data;

	ASSERT(entry);

	vmci_signal_event(&entry->destroy_event);

	/*
	 * The entry is freed in vmci_datagram_destroy_hnd, who is waiting for
	 * the above signal.
	 */
}