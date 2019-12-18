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
struct nmreq_register {int /*<<< orphan*/  nr_extra_bufs; int /*<<< orphan*/  nr_mem_id; int /*<<< orphan*/  nr_rx_rings; int /*<<< orphan*/  nr_tx_rings; int /*<<< orphan*/  nr_rx_slots; int /*<<< orphan*/  nr_tx_slots; int /*<<< orphan*/  nr_memsize; int /*<<< orphan*/  nr_offset; } ;
struct nmreq {int /*<<< orphan*/  nr_arg3; int /*<<< orphan*/  nr_arg2; int /*<<< orphan*/  nr_rx_rings; int /*<<< orphan*/  nr_tx_rings; int /*<<< orphan*/  nr_rx_slots; int /*<<< orphan*/  nr_tx_slots; int /*<<< orphan*/  nr_memsize; int /*<<< orphan*/  nr_offset; } ;

/* Variables and functions */

__attribute__((used)) static void
nmreq_register_to_legacy(const struct nmreq_register *req, struct nmreq *nmr)
{
	nmr->nr_offset = req->nr_offset;
	nmr->nr_memsize = req->nr_memsize;
	nmr->nr_tx_slots = req->nr_tx_slots;
	nmr->nr_rx_slots = req->nr_rx_slots;
	nmr->nr_tx_rings = req->nr_tx_rings;
	nmr->nr_rx_rings = req->nr_rx_rings;
	nmr->nr_arg2 = req->nr_mem_id;
	nmr->nr_arg3 = req->nr_extra_bufs;
}