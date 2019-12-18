#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nstime_t ;
struct TYPE_6__ {int /*<<< orphan*/  epoch; int /*<<< orphan*/  const interval; } ;
typedef  TYPE_1__ arena_decay_t ;

/* Variables and functions */
 int /*<<< orphan*/  arena_decay_backlog_update (TYPE_1__*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  arena_decay_deadline_init (TYPE_1__*) ; 
 int arena_decay_deadline_reached (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nstime_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nstime_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ nstime_divide (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  nstime_imultiply (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  nstime_subtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_decay_epoch_advance_helper(arena_decay_t *decay, const nstime_t *time,
    size_t current_npages) {
	assert(arena_decay_deadline_reached(decay, time));

	nstime_t delta;
	nstime_copy(&delta, time);
	nstime_subtract(&delta, &decay->epoch);

	uint64_t nadvance_u64 = nstime_divide(&delta, &decay->interval);
	assert(nadvance_u64 > 0);

	/* Add nadvance_u64 decay intervals to epoch. */
	nstime_copy(&delta, &decay->interval);
	nstime_imultiply(&delta, nadvance_u64);
	nstime_add(&decay->epoch, &delta);

	/* Set a new deadline. */
	arena_decay_deadline_init(decay);

	/* Update the backlog. */
	arena_decay_backlog_update(decay, nadvance_u64, current_npages);
}