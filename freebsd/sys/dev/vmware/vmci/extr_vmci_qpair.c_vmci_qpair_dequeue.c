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
struct vmci_qpair {int flags; int /*<<< orphan*/  consume_q_size; int /*<<< orphan*/  consume_q; int /*<<< orphan*/  produce_q; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_QPFLAG_LOCAL ; 
 int VMCI_QPFLAG_NONBLOCK ; 
 int /*<<< orphan*/  dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vmci_memcpy_from_queue ; 
 int /*<<< orphan*/  vmci_memcpy_from_queue_local ; 

ssize_t
vmci_qpair_dequeue(struct vmci_qpair *qpair, void *buf, size_t buf_size,
    int buf_type)
{
	ssize_t result;

	if (!qpair || !buf)
		return (VMCI_ERROR_INVALID_ARGS);

	result = dequeue(qpair->produce_q, qpair->consume_q,
	    qpair->consume_q_size, buf, buf_size, buf_type,
	    qpair->flags & VMCI_QPFLAG_LOCAL?
	    vmci_memcpy_from_queue_local : vmci_memcpy_from_queue, true,
	    !(qpair->flags & VMCI_QPFLAG_NONBLOCK));

	return (result);
}