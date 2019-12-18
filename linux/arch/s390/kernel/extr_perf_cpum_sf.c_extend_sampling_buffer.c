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
struct sf_buffer {unsigned long num_sdb; } ;
struct hw_perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  debug_sprintf_event (int /*<<< orphan*/ ,int,char*,unsigned long,...) ; 
 int realloc_sampling_buffer (struct sf_buffer*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sf_disable () ; 
 scalar_t__ sfb_has_pending_allocs (struct sf_buffer*,struct hw_perf_event*) ; 
 unsigned long sfb_pending_allocs (struct sf_buffer*,struct hw_perf_event*) ; 
 int /*<<< orphan*/  sfdbg ; 

__attribute__((used)) static void extend_sampling_buffer(struct sf_buffer *sfb,
				   struct hw_perf_event *hwc)
{
	unsigned long num, num_old;
	int rc;

	num = sfb_pending_allocs(sfb, hwc);
	if (!num)
		return;
	num_old = sfb->num_sdb;

	/* Disable the sampling facility to reset any states and also
	 * clear pending measurement alerts.
	 */
	sf_disable();

	/* Extend the sampling buffer.
	 * This memory allocation typically happens in an atomic context when
	 * called by perf.  Because this is a reallocation, it is fine if the
	 * new SDB-request cannot be satisfied immediately.
	 */
	rc = realloc_sampling_buffer(sfb, num, GFP_ATOMIC);
	if (rc)
		debug_sprintf_event(sfdbg, 5, "sfb: extend: realloc "
				    "failed with rc=%i\n", rc);

	if (sfb_has_pending_allocs(sfb, hwc))
		debug_sprintf_event(sfdbg, 5, "sfb: extend: "
				    "req=%lu alloc=%lu remaining=%lu\n",
				    num, sfb->num_sdb - num_old,
				    sfb_pending_allocs(sfb, hwc));
}