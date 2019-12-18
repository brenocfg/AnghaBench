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
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  gs_mtx; int /*<<< orphan*/  gs_pending; int /*<<< orphan*/  gs_npending; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 TYPE_1__ me ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_sched_temporary_start(struct bio *bio)
{

	mtx_lock(&me.gs_mtx);
	me.gs_npending++;
	bioq_disksort(&me.gs_pending, bio);
	mtx_unlock(&me.gs_mtx);
}