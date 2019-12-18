#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
typedef  int /*<<< orphan*/  tcache_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_4__ {TYPE_1__ cur_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ config_debug ; 
 int /*<<< orphan*/  tcache_available (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcache_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* tcache_small_bin_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int tsd_tcache_enabled_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsd_tcachep_get (int /*<<< orphan*/ *) ; 

void
tcache_cleanup(tsd_t *tsd) {
	tcache_t *tcache = tsd_tcachep_get(tsd);
	if (!tcache_available(tsd)) {
		assert(tsd_tcache_enabled_get(tsd) == false);
		if (config_debug) {
			assert(tcache_small_bin_get(tcache, 0)->cur_ptr.ptr
			    == NULL);
		}
		return;
	}
	assert(tsd_tcache_enabled_get(tsd));
	assert(tcache_small_bin_get(tcache, 0)->cur_ptr.ptr != NULL);

	tcache_destroy(tsd, tcache, true);
	if (config_debug) {
		tcache_small_bin_get(tcache, 0)->cur_ptr.ptr = NULL;
	}
}