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
struct TYPE_2__ {int /*<<< orphan*/ * tq; int /*<<< orphan*/  work; } ;
struct lio {TYPE_1__ rx_status_tq; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 struct lio* if_getsoftc (struct ifnet*) ; 
 scalar_t__ taskqueue_cancel_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lio_cleanup_rx_oom_poll_fn(struct ifnet *ifp)
{
	struct lio	*lio = if_getsoftc(ifp);

	if (lio->rx_status_tq.tq != NULL) {
		while (taskqueue_cancel_timeout(lio->rx_status_tq.tq,
						&lio->rx_status_tq.work, NULL))
			taskqueue_drain_timeout(lio->rx_status_tq.tq,
						&lio->rx_status_tq.work);

		taskqueue_free(lio->rx_status_tq.tq);

		lio->rx_status_tq.tq = NULL;
	}
}