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

/* Variables and functions */
 int /*<<< orphan*/  WITNESS_RANK_CTL ; 
 int ctl_initialized ; 
 int /*<<< orphan*/  ctl_mtx ; 
 scalar_t__ malloc_mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_rank_exclusive ; 

bool
ctl_boot(void) {
	if (malloc_mutex_init(&ctl_mtx, "ctl", WITNESS_RANK_CTL,
	    malloc_mutex_rank_exclusive)) {
		return true;
	}

	ctl_initialized = false;

	return false;
}