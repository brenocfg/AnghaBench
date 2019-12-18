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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  arena_decay_ms_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_zd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  muzzy_decay_ms_default ; 

bool
arena_muzzy_decay_ms_default_set(ssize_t decay_ms) {
	if (!arena_decay_ms_valid(decay_ms)) {
		return true;
	}
	atomic_store_zd(&muzzy_decay_ms_default, decay_ms, ATOMIC_RELAXED);
	return false;
}