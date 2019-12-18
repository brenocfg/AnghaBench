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
struct vmci_queue_header {int dummy; } ;
struct vmci_qpair {int /*<<< orphan*/  produce_q_size; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  vmci_qpair_get_queue_headers (struct vmci_qpair const*,struct vmci_queue_header**,struct vmci_queue_header**) ; 
 int /*<<< orphan*/  vmci_queue_header_buf_ready (struct vmci_queue_header*,struct vmci_queue_header*,int /*<<< orphan*/ ) ; 

int64_t
vmci_qpair_produce_buf_ready(const struct vmci_qpair *qpair)
{
	struct vmci_queue_header *consume_q_header;
	struct vmci_queue_header *produce_q_header;
	int64_t result;

	if (!qpair)
		return (VMCI_ERROR_INVALID_ARGS);

	vmci_qpair_get_queue_headers(qpair, &produce_q_header,
	    &consume_q_header);
	result = vmci_queue_header_buf_ready(produce_q_header, consume_q_header,
	    qpair->produce_q_size);

	return (result);
}