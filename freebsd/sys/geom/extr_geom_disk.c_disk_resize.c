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
struct disk {int /*<<< orphan*/ * d_geom; scalar_t__ d_destroyed; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_disk_resize ; 
 int g_post_event (int /*<<< orphan*/ ,struct disk*,int,int /*<<< orphan*/ *) ; 

int
disk_resize(struct disk *dp, int flag)
{

	if (dp->d_destroyed || dp->d_geom == NULL)
		return (0);

	return (g_post_event(g_disk_resize, dp, flag, NULL));
}