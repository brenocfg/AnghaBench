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
typedef  int /*<<< orphan*/  uint16_t ;
struct ena_ring {int first_interrupt; scalar_t__ no_interrupt_event_cnt; int /*<<< orphan*/  ena_dev; struct ena_adapter* adapter; int /*<<< orphan*/  qid; } ;
struct ena_adapter {int /*<<< orphan*/  ena_dev; } ;

/* Variables and functions */

__attribute__((used)) static void
ena_init_io_rings_common(struct ena_adapter *adapter, struct ena_ring *ring,
    uint16_t qid)
{

	ring->qid = qid;
	ring->adapter = adapter;
	ring->ena_dev = adapter->ena_dev;
	ring->first_interrupt = false;
	ring->no_interrupt_event_cnt = 0;
}