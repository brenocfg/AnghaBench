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
struct octeon_device {int /*<<< orphan*/  octeon_id; } ;
struct lio_tq {int /*<<< orphan*/  work; int /*<<< orphan*/ * tq; struct lio* ctxptr; } ;
struct lio {struct lio_tq rx_status_tq; struct octeon_device* oct_dev; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PI_NET ; 
 int /*<<< orphan*/  TIMEOUT_TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 struct lio* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_ms_to_ticks (int) ; 
 int /*<<< orphan*/  lio_poll_check_rx_oom_status ; 
 int /*<<< orphan*/ * taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_enqueue_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

__attribute__((used)) static int
lio_setup_rx_oom_poll_fn(struct ifnet *ifp)
{
	struct lio	*lio = if_getsoftc(ifp);
	struct octeon_device	*oct = lio->oct_dev;
	struct lio_tq	*rx_status_tq;

	rx_status_tq = &lio->rx_status_tq;

	rx_status_tq->tq = taskqueue_create("lio_rx_oom_status", M_WAITOK,
					    taskqueue_thread_enqueue,
					    &rx_status_tq->tq);
	if (rx_status_tq->tq == NULL) {
		lio_dev_err(oct, "unable to create lio rx oom status tq\n");
		return (-1);
	}

	TIMEOUT_TASK_INIT(rx_status_tq->tq, &rx_status_tq->work, 0,
			  lio_poll_check_rx_oom_status, (void *)rx_status_tq);

	rx_status_tq->ctxptr = lio;

	taskqueue_start_threads(&rx_status_tq->tq, 1, PI_NET,
				"lio%d_rx_oom_status",
				oct->octeon_id);

	taskqueue_enqueue_timeout(rx_status_tq->tq, &rx_status_tq->work,
				  lio_ms_to_ticks(50));

	return (0);
}