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
struct vmci_handle {int dummy; } ;
struct vmci_queue_header {struct vmci_handle handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmci_queue_header_reset_pointers (struct vmci_queue_header*) ; 

__attribute__((used)) static inline void
vmci_queue_header_init(struct vmci_queue_header *q_header,
    const struct vmci_handle handle)
{

	q_header->handle = handle;
	vmci_queue_header_reset_pointers(q_header);
}