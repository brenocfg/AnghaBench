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
struct pfr_kcounters {scalar_t__ pfrkc_tzero; void*** pfrkc_bytes; void*** pfrkc_packets; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 void* counter_u64_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
pfr_create_kentry_counter(struct pfr_kcounters *kc, int pfr_dir, int pfr_op)
{
	kc->pfrkc_packets[pfr_dir][pfr_op] = counter_u64_alloc(M_NOWAIT);
	if (! kc->pfrkc_packets[pfr_dir][pfr_op])
		return (false);

	kc->pfrkc_bytes[pfr_dir][pfr_op] = counter_u64_alloc(M_NOWAIT);
	if (! kc->pfrkc_bytes[pfr_dir][pfr_op]) {
		/* Previous allocation will be freed through
		 * pfr_destroy_kentry() */
		return (false);
	}

	kc->pfrkc_tzero = 0;

	return (true);
}