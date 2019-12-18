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
 int /*<<< orphan*/  qp_add_pointer (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
vmci_queue_header_add_consumer_head(struct vmci_queue_header *q_header,
    size_t add, uint64_t queue_size)
{

	qp_add_pointer(&q_header->consumer_head, add, queue_size);
}