#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {int jitter_state; int /*<<< orphan*/  backlog; scalar_t__ nunpurged; int /*<<< orphan*/  epoch; int /*<<< orphan*/  interval; } ;
typedef  TYPE_1__ arena_decay_t ;

/* Variables and functions */
 int KQU (int) ; 
 int SMOOTHSTEP_NSTEPS ; 
 int /*<<< orphan*/  arena_decay_deadline_init (TYPE_1__*) ; 
 int /*<<< orphan*/  arena_decay_ms_write (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nstime_idivide (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nstime_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nstime_update (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
arena_decay_reinit(arena_decay_t *decay, ssize_t decay_ms) {
	arena_decay_ms_write(decay, decay_ms);
	if (decay_ms > 0) {
		nstime_init(&decay->interval, (uint64_t)decay_ms *
		    KQU(1000000));
		nstime_idivide(&decay->interval, SMOOTHSTEP_NSTEPS);
	}

	nstime_init(&decay->epoch, 0);
	nstime_update(&decay->epoch);
	decay->jitter_state = (uint64_t)(uintptr_t)decay;
	arena_decay_deadline_init(decay);
	decay->nunpurged = 0;
	memset(decay->backlog, 0, SMOOTHSTEP_NSTEPS * sizeof(size_t));
}