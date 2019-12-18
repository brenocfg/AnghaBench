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
struct hv_vss_req_internal {int /*<<< orphan*/  callout; } ;
struct TYPE_5__ {int /*<<< orphan*/  to_ack_queue; int /*<<< orphan*/  to_notify_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  to_ack_queue; int /*<<< orphan*/  to_notify_queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  pending_mutex; int /*<<< orphan*/  req_free_list; TYPE_2__ app_sc; TYPE_1__ daemon_sc; } ;
typedef  TYPE_3__ hv_vss_sc ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct hv_vss_req_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 struct hv_vss_req_internal* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hv_vss_init_send_receive_queue(device_t dev)
{
	hv_vss_sc *sc = (hv_vss_sc*)device_get_softc(dev);
	int i;
	const int max_list = 4; /* It is big enough for the list */
	struct hv_vss_req_internal* reqp;

	LIST_INIT(&sc->req_free_list);
	STAILQ_INIT(&sc->daemon_sc.to_notify_queue);
	STAILQ_INIT(&sc->daemon_sc.to_ack_queue);
	STAILQ_INIT(&sc->app_sc.to_notify_queue);
	STAILQ_INIT(&sc->app_sc.to_ack_queue);

	for (i = 0; i < max_list; i++) {
		reqp = malloc(sizeof(struct hv_vss_req_internal),
		    M_DEVBUF, M_WAITOK|M_ZERO);
		LIST_INSERT_HEAD(&sc->req_free_list, reqp, link);
		callout_init_mtx(&reqp->callout, &sc->pending_mutex, 0);
	}
	return (0);
}