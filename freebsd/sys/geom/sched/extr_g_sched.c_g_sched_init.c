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
 int /*<<< orphan*/  G_SCHED_DEBUG (int /*<<< orphan*/ ,char*,struct g_class*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_classifier_ini () ; 
 int /*<<< orphan*/  g_gsched_global_init () ; 
 int /*<<< orphan*/  g_sched_class ; 

__attribute__((used)) static void
g_sched_init(struct g_class *mp)
{

	g_gsched_global_init();

	G_SCHED_DEBUG(0, "Loading: mp = %p, g_sched_class = %p.",
	    mp, &g_sched_class);

	/* Patch g_io_request to store classification info in the bio. */
	g_classifier_ini();
}