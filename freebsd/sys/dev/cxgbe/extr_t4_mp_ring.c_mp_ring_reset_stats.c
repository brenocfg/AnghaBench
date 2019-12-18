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
struct mp_ring {int /*<<< orphan*/  abdications; int /*<<< orphan*/  restarts; int /*<<< orphan*/  stalls; int /*<<< orphan*/  starts; int /*<<< orphan*/  drops; int /*<<< orphan*/  enqueues; } ;

/* Variables and functions */
 int /*<<< orphan*/  counter_u64_zero (int /*<<< orphan*/ ) ; 

void
mp_ring_reset_stats(struct mp_ring *r)
{

	counter_u64_zero(r->enqueues);
	counter_u64_zero(r->drops);
	counter_u64_zero(r->starts);
	counter_u64_zero(r->stalls);
	counter_u64_zero(r->restarts);
	counter_u64_zero(r->abdications);
}