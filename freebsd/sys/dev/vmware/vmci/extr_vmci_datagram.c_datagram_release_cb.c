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
struct datagram_entry {int /*<<< orphan*/  resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (struct datagram_entry*) ; 
 int /*<<< orphan*/  vmci_resource_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
datagram_release_cb(void *client_data)
{
	struct datagram_entry *entry;

	entry = (struct datagram_entry *)client_data;

	ASSERT(entry);

	vmci_resource_release(&entry->resource);

	return (0);
}