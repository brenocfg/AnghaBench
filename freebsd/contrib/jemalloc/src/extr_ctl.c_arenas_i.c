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
typedef  int /*<<< orphan*/  ctl_arena_t ;

/* Variables and functions */
 int /*<<< orphan*/ * arenas_i_impl (int /*<<< orphan*/ ,size_t,int,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsd_fetch () ; 

__attribute__((used)) static ctl_arena_t *
arenas_i(size_t i) {
	ctl_arena_t *ret = arenas_i_impl(tsd_fetch(), i, true, false);
	assert(ret != NULL);
	return ret;
}