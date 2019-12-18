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
struct wakeup_source {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wakeup_source_destroy (struct wakeup_source*) ; 
 int /*<<< orphan*/  wakeup_source_remove (struct wakeup_source*) ; 
 int /*<<< orphan*/  wakeup_source_sysfs_remove (struct wakeup_source*) ; 

void wakeup_source_unregister(struct wakeup_source *ws)
{
	if (ws) {
		wakeup_source_remove(ws);
		wakeup_source_sysfs_remove(ws);
		wakeup_source_destroy(ws);
	}
}