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
typedef  int /*<<< orphan*/  tcache_t ;

/* Variables and functions */
 scalar_t__ TCACHE_GC_INCR_BYTES ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  tcache_event_hard (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int tcache_gc_event_wait_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tcache_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_tcache_gc_event_update (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
thread_tcache_gc_event_handler(tsd_t *tsd) {
	assert(TCACHE_GC_INCR_BYTES > 0);
	assert(tcache_gc_event_wait_get(tsd) == 0U);
	thread_tcache_gc_event_update(tsd, TCACHE_GC_INCR_BYTES);
	tcache_t *tcache = tcache_get(tsd);
	if (tcache != NULL) {
		tcache_event_hard(tsd, tcache);
	}
}