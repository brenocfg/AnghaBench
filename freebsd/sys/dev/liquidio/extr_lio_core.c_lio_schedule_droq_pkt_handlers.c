#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_2__ {int oq; } ;
struct octeon_device {int int_status; struct lio_droq** droq; TYPE_1__ io_qmask; } ;
struct lio_droq {int /*<<< orphan*/  droq_task; int /*<<< orphan*/  droq_taskqueue; } ;

/* Variables and functions */
 int BIT_ULL (size_t) ; 
 int LIO_DEV_INTR_PKT_DATA ; 
 size_t LIO_MAX_OUTPUT_QUEUES (struct octeon_device*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lio_schedule_droq_pkt_handlers(struct octeon_device *oct)
{
	struct lio_droq	*droq;
	uint64_t	oq_no;

	if (oct->int_status & LIO_DEV_INTR_PKT_DATA) {
		for (oq_no = 0; oq_no < LIO_MAX_OUTPUT_QUEUES(oct); oq_no++) {
			if (!(oct->io_qmask.oq & BIT_ULL(oq_no)))
				continue;

			droq = oct->droq[oq_no];

			taskqueue_enqueue(droq->droq_taskqueue,
					  &droq->droq_task);
		}
	}
}