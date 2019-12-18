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
struct g_class {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct g_class*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_MIRROR_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_FIRST ; 
 int /*<<< orphan*/ * g_mirror_post_sync ; 
 int /*<<< orphan*/  g_mirror_shutdown_post_sync ; 
 int /*<<< orphan*/  shutdown_post_sync ; 

__attribute__((used)) static void
g_mirror_init(struct g_class *mp)
{

	g_mirror_post_sync = EVENTHANDLER_REGISTER(shutdown_post_sync,
	    g_mirror_shutdown_post_sync, mp, SHUTDOWN_PRI_FIRST);
	if (g_mirror_post_sync == NULL)
		G_MIRROR_DEBUG(0, "Warning! Cannot register shutdown event.");
}