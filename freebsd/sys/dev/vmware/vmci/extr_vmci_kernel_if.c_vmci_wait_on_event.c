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
typedef  int /*<<< orphan*/  (* vmci_event_release_cb ) (void*) ;
typedef  int /*<<< orphan*/  vmci_event ;

/* Variables and functions */
 int /*<<< orphan*/  sema_wait (int /*<<< orphan*/ *) ; 

void
vmci_wait_on_event(vmci_event *event, vmci_event_release_cb release_cb,
    void *client_data)
{

	release_cb(client_data);
	sema_wait(event);
}