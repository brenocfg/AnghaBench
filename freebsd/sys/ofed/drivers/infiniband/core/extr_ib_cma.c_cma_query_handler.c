#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rdma_route {int num_paths; struct ib_sa_path_rec* path_rec; } ;
struct ib_sa_path_rec {int dummy; } ;
struct TYPE_4__ {int status; int /*<<< orphan*/  event; } ;
struct cma_work {int /*<<< orphan*/  work; TYPE_1__ event; int /*<<< orphan*/  new_state; int /*<<< orphan*/  old_state; TYPE_3__* id; } ;
struct TYPE_5__ {struct rdma_route route; } ;
struct TYPE_6__ {TYPE_2__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_CM_ADDR_RESOLVED ; 
 int /*<<< orphan*/  RDMA_CM_EVENT_ROUTE_ERROR ; 
 int /*<<< orphan*/  RDMA_CM_ROUTE_QUERY ; 
 int /*<<< orphan*/  cma_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cma_query_handler(int status, struct ib_sa_path_rec *path_rec,
			      void *context)
{
	struct cma_work *work = context;
	struct rdma_route *route;

	route = &work->id->id.route;

	if (!status) {
		route->num_paths = 1;
		*route->path_rec = *path_rec;
	} else {
		work->old_state = RDMA_CM_ROUTE_QUERY;
		work->new_state = RDMA_CM_ADDR_RESOLVED;
		work->event.event = RDMA_CM_EVENT_ROUTE_ERROR;
		work->event.status = status;
	}

	queue_work(cma_wq, &work->work);
}