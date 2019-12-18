#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nstime_t ;
struct TYPE_4__ {int /*<<< orphan*/  deadline; int /*<<< orphan*/  interval; int /*<<< orphan*/  jitter_state; int /*<<< orphan*/  epoch; } ;
typedef  TYPE_1__ arena_decay_t ;

/* Variables and functions */
 scalar_t__ arena_decay_ms_read (TYPE_1__*) ; 
 int /*<<< orphan*/  nstime_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nstime_ns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prng_range_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arena_decay_deadline_init(arena_decay_t *decay) {
	/*
	 * Generate a new deadline that is uniformly random within the next
	 * epoch after the current one.
	 */
	nstime_copy(&decay->deadline, &decay->epoch);
	nstime_add(&decay->deadline, &decay->interval);
	if (arena_decay_ms_read(decay) > 0) {
		nstime_t jitter;

		nstime_init(&jitter, prng_range_u64(&decay->jitter_state,
		    nstime_ns(&decay->interval)));
		nstime_add(&decay->deadline, &jitter);
	}
}