#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vmci_queue_header {int dummy; } ;
struct vmci_qpair {TYPE_2__* consume_q; TYPE_1__* produce_q; } ;
struct TYPE_4__ {struct vmci_queue_header* q_header; } ;
struct TYPE_3__ {struct vmci_queue_header* q_header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 

__attribute__((used)) static void
vmci_qpair_get_queue_headers(const struct vmci_qpair *qpair,
    struct vmci_queue_header **produce_q_header,
    struct vmci_queue_header **consume_q_header)
{

	ASSERT((qpair->produce_q != NULL) && (qpair->consume_q != NULL));
	*produce_q_header = qpair->produce_q->q_header;
	*consume_q_header = qpair->consume_q->q_header;
}