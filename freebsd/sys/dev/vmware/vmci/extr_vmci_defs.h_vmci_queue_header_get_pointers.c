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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmci_queue_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vmci_queue_header_consumer_head (struct vmci_queue_header const*) ; 
 int /*<<< orphan*/  vmci_queue_header_producer_tail (struct vmci_queue_header const*) ; 

__attribute__((used)) static inline void
vmci_queue_header_get_pointers(const struct vmci_queue_header *produce_q_header,
    const struct vmci_queue_header *consume_q_header, uint64_t *producer_tail,
    uint64_t *consumer_head)
{

	if (producer_tail)
		*producer_tail =
		    vmci_queue_header_producer_tail(produce_q_header);

	if (consumer_head)
		*consumer_head =
		    vmci_queue_header_consumer_head(consume_q_header);
}