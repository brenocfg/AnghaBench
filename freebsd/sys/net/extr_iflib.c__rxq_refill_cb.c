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
struct rxq_refill_cb_arg {int error; int nseg; int /*<<< orphan*/  seg; } ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */

__attribute__((used)) static void
_rxq_refill_cb(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct rxq_refill_cb_arg *cb_arg = arg;

	cb_arg->error = error;
	cb_arg->seg = segs[0];
	cb_arg->nseg = nseg;
}