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
struct nmdmpart {scalar_t__ np_rate; int np_accumulator; int np_quota; int /*<<< orphan*/  np_callout; int /*<<< orphan*/  np_task; scalar_t__ np_credits; } ;

/* Variables and functions */
 int QS ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,scalar_t__,void (*) (void*),struct nmdmpart*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static void
nmdm_timeout(void *arg)
{
	struct nmdmpart *np = arg;

	if (np->np_rate == 0)
		return;

	/*
	 * Do a simple Floyd-Steinberg dither here to avoid FP math.
	 * Wipe out unused quota from last tick.
	 */
	np->np_accumulator += np->np_credits;
	np->np_quota = np->np_accumulator >> QS;
	np->np_accumulator &= ((1 << QS) - 1);

	taskqueue_enqueue(taskqueue_swi, &np->np_task);
	callout_reset(&np->np_callout, np->np_rate, nmdm_timeout, np);
}