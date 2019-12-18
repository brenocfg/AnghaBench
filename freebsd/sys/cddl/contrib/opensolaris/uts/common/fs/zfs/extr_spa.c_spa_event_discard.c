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
typedef  int /*<<< orphan*/  sysevent_t ;

/* Variables and functions */
 int /*<<< orphan*/  sysevent_free (int /*<<< orphan*/ *) ; 

void
spa_event_discard(sysevent_t *ev)
{
#ifdef _KERNEL
	sysevent_free(ev);
#endif
}