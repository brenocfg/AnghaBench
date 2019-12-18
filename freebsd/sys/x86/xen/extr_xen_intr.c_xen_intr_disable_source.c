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
struct xenisrc {int xi_masked; int /*<<< orphan*/  xi_port; } ;
struct intsrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  evtchn_test_and_set_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xen_intr_disable_source(struct intsrc *base_isrc, int eoi)
{
	struct xenisrc *isrc;

	isrc = (struct xenisrc *)base_isrc;

	/*
	 * NB: checking if the event channel is already masked is
	 * needed because the event channel user-space device
	 * masks event channels on its filter as part of its
	 * normal operation, and those shouldn't be automatically
	 * unmasked by the generic interrupt code. The event channel
	 * device will unmask them when needed.
	 */
	isrc->xi_masked = !!evtchn_test_and_set_mask(isrc->xi_port);
}