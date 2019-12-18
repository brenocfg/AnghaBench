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
struct TYPE_2__ {int gs_initialized; int /*<<< orphan*/  gs_pending; int /*<<< orphan*/  gs_scheds; int /*<<< orphan*/  gs_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_SCHED_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ me ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
g_gsched_global_init(void)
{

	if (!me.gs_initialized) {
		G_SCHED_DEBUG(0, "Initializing global data.");
		mtx_init(&me.gs_mtx, "gsched", NULL, MTX_DEF);
		LIST_INIT(&me.gs_scheds);
		bioq_init(&me.gs_pending);
		me.gs_initialized = 1;
	}
}