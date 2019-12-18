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
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_eli_pre_sync ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 

__attribute__((used)) static void
g_eli_fini(struct g_class *mp)
{

	if (g_eli_pre_sync != NULL)
		EVENTHANDLER_DEREGISTER(shutdown_pre_sync, g_eli_pre_sync);
}