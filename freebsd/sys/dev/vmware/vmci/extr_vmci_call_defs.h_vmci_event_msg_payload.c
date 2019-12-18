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
struct vmci_event_msg {int /*<<< orphan*/  event_data; } ;

/* Variables and functions */
 void* vmci_event_data_payload (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void *
vmci_event_msg_payload(struct vmci_event_msg *e_msg)
{

	return (vmci_event_data_payload(&e_msg->event_data));
}