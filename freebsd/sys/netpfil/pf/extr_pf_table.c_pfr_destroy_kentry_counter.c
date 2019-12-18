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
struct pfr_kcounters {int /*<<< orphan*/ ** pfrkc_bytes; int /*<<< orphan*/ ** pfrkc_packets; } ;

/* Variables and functions */
 int /*<<< orphan*/  counter_u64_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pfr_destroy_kentry_counter(struct pfr_kcounters *kc, int pfr_dir, int pfr_op)
{
	counter_u64_free(kc->pfrkc_packets[pfr_dir][pfr_op]);
	counter_u64_free(kc->pfrkc_bytes[pfr_dir][pfr_op]);
}