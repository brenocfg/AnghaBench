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
struct vmci_qpair {scalar_t__ produce_q_size; } ;

/* Variables and functions */
 int VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_ERROR_INVALID_SIZE ; 
 int VMCI_SUCCESS ; 
 int /*<<< orphan*/  vmci_qpair_get_queue_headers (struct vmci_qpair const*,struct vmci_queue_header**,struct vmci_queue_header**) ; 
 int /*<<< orphan*/  vmci_queue_header_get_pointers (struct vmci_queue_header*,struct vmci_queue_header*,scalar_t__*,scalar_t__*) ; 

int
vmci_qpair_get_produce_indexes(const struct vmci_qpair *qpair,
    uint64_t *producer_tail, uint64_t *consumer_head)
{
	struct vmci_queue_header *consume_q_header;
	struct vmci_queue_header *produce_q_header;

	if (!qpair)
		return (VMCI_ERROR_INVALID_ARGS);

	vmci_qpair_get_queue_headers(qpair, &produce_q_header,
	    &consume_q_header);
	vmci_queue_header_get_pointers(produce_q_header, consume_q_header,
	    producer_tail, consumer_head);

	if ((producer_tail && *producer_tail >= qpair->produce_q_size) ||
	    (consumer_head && *consumer_head >= qpair->produce_q_size))
		return (VMCI_ERROR_INVALID_SIZE);

	return (VMCI_SUCCESS);
}