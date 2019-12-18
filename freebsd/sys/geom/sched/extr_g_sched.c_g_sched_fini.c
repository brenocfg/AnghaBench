#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct g_class {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gs_mtx; int /*<<< orphan*/  gs_scheds; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_SCHED_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_classifier_fini () ; 
 TYPE_1__ me ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_sched_fini(struct g_class *mp)
{

	g_classifier_fini();

	G_SCHED_DEBUG(0, "Unloading...");

	KASSERT(LIST_EMPTY(&me.gs_scheds), ("still registered schedulers"));
	mtx_destroy(&me.gs_mtx);
}