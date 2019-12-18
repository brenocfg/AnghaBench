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
struct bio {int dummy; } ;

/* Variables and functions */
 scalar_t__ GKT_RUN ; 
 int /*<<< orphan*/  PRIBIO ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_multipath_done_error (struct bio*) ; 
 scalar_t__ g_multipath_kt_state ; 
 int /*<<< orphan*/  gmtbq ; 
 int /*<<< orphan*/  gmtbq_mtx ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
g_multipath_kt(void *arg)
{

	g_multipath_kt_state = GKT_RUN;
	mtx_lock(&gmtbq_mtx);
	while (g_multipath_kt_state == GKT_RUN) {
		for (;;) {
			struct bio *bp;

			bp = bioq_takefirst(&gmtbq);
			if (bp == NULL)
				break;
			mtx_unlock(&gmtbq_mtx);
			g_multipath_done_error(bp);
			mtx_lock(&gmtbq_mtx);
		}
		if (g_multipath_kt_state != GKT_RUN)
			break;
		msleep(&g_multipath_kt_state, &gmtbq_mtx, PRIBIO,
		    "gkt:wait", 0);
	}
	mtx_unlock(&gmtbq_mtx);
	wakeup(&g_multipath_kt_state);
	kproc_exit(0);
}