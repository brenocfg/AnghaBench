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
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sndstat_dev ; 
 int /*<<< orphan*/  sndstat_lock ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sndstat_sysuninit(void *p)
{
	if (sndstat_dev != NULL) {
		/* destroy_dev() will wait for all references to go away */
		destroy_dev(sndstat_dev);
	}
	sx_destroy(&sndstat_lock);
}