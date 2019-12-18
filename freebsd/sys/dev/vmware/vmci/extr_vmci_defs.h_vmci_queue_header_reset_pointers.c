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
struct vmci_queue_header {int /*<<< orphan*/  consumer_head; int /*<<< orphan*/  producer_tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONST64U (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qp_atomic_write_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vmci_queue_header_reset_pointers(struct vmci_queue_header *q_header)
{

	qp_atomic_write_offset(&q_header->producer_tail, CONST64U(0));
	qp_atomic_write_offset(&q_header->consumer_head, CONST64U(0));
}