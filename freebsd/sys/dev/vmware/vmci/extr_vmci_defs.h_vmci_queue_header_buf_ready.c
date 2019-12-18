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
typedef  scalar_t__ uint64_t ;
struct vmci_queue_header {int dummy; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ VMCI_SUCCESS ; 
 scalar_t__ vmci_queue_header_free_space (struct vmci_queue_header const*,struct vmci_queue_header const*,scalar_t__ const) ; 

__attribute__((used)) static inline int64_t
vmci_queue_header_buf_ready(const struct vmci_queue_header *consume_q_header,
    const struct vmci_queue_header *produce_q_header,
    const uint64_t consume_q_size)
{
	int64_t free_space;

	free_space = vmci_queue_header_free_space(consume_q_header,
	    produce_q_header, consume_q_size);
	if (free_space < VMCI_SUCCESS)
		return (free_space);
	else
		return (consume_q_size - free_space - 1);
}