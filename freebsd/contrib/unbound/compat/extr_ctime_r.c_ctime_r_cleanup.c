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
 int /*<<< orphan*/  ctime_lock ; 
 scalar_t__ ctime_r_init ; 
 int /*<<< orphan*/  lock_basic_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ctime_r_cleanup(void)
{
	if(ctime_r_init) {
		ctime_r_init = 0;
		lock_basic_destroy(&ctime_lock);
	}
}