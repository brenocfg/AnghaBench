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
struct vmci_qpair {int flags; int /*<<< orphan*/  produce_q_size; int /*<<< orphan*/  consume_q; int /*<<< orphan*/  produce_q; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  VMCI_ERROR_INVALID_ARGS ; 
 int VMCI_QPFLAG_LOCAL ; 
 int VMCI_QPFLAG_NONBLOCK ; 
 int /*<<< orphan*/  enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmci_memcpy_to_queue_v ; 
 int /*<<< orphan*/  vmci_memcpy_to_queue_v_local ; 

ssize_t
vmci_qpair_enquev(struct vmci_qpair *qpair, void *iov, size_t iov_size,
    int buf_type)
{
	ssize_t result;

	if (!qpair || !iov)
		return (VMCI_ERROR_INVALID_ARGS);

	result = enqueue(qpair->produce_q, qpair->consume_q,
	    qpair->produce_q_size, iov, iov_size, buf_type,
	    qpair->flags & VMCI_QPFLAG_LOCAL?
	    vmci_memcpy_to_queue_v_local : vmci_memcpy_to_queue_v,
	    !(qpair->flags & VMCI_QPFLAG_NONBLOCK));

	return (result);
}