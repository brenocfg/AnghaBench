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
struct disk {int d_destroyed; int /*<<< orphan*/ * d_devstat; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  devstat_remove_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_cancel_event (struct disk*) ; 
 int /*<<< orphan*/  g_disk_destroy ; 
 int /*<<< orphan*/  g_post_event (int /*<<< orphan*/ ,struct disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
disk_destroy(struct disk *dp)
{

	g_cancel_event(dp);
	dp->d_destroyed = 1;
	if (dp->d_devstat != NULL)
		devstat_remove_entry(dp->d_devstat);
	g_post_event(g_disk_destroy, dp, M_WAITOK, NULL);
}