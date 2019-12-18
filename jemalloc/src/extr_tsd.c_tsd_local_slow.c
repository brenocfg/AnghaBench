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
 scalar_t__ tsd_reentrancy_level_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsd_tcache_enabled_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
tsd_local_slow(tsd_t *tsd) {
	return !tsd_tcache_enabled_get(tsd)
	    || tsd_reentrancy_level_get(tsd) > 0;
}