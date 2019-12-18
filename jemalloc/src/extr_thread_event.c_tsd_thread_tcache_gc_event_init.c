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
typedef  int /*<<< orphan*/  tsd_t ;

/* Variables and functions */
 scalar_t__ TCACHE_GC_INCR_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  thread_tcache_gc_event_update (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
tsd_thread_tcache_gc_event_init(tsd_t *tsd) {
	assert(TCACHE_GC_INCR_BYTES > 0);
	thread_tcache_gc_event_update(tsd, TCACHE_GC_INCR_BYTES);
}