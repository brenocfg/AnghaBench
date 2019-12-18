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
struct vmci_queue_header {int /*<<< orphan*/  consumer_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  qp_atomic_read_offset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline uint64_t
vmci_queue_header_consumer_head(const struct vmci_queue_header *q_header)
{
	struct vmci_queue_header *qh = (struct vmci_queue_header *)q_header;
	return (qp_atomic_read_offset(&qh->consumer_head));
}