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
struct TYPE_5__ {int /*<<< orphan*/  to_ack_queue; int /*<<< orphan*/  to_notify_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  to_ack_queue; int /*<<< orphan*/  to_notify_queue; } ;
struct TYPE_6__ {TYPE_2__ app_sc; TYPE_1__ daemon_sc; int /*<<< orphan*/  req_free_list; } ;
typedef  TYPE_3__ hv_vss_sc ;
typedef  int /*<<< orphan*/  hv_vss_req_internal ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  slink ; 

__attribute__((used)) static int
hv_vss_destroy_send_receive_queue(device_t dev)
{
	hv_vss_sc *sc = (hv_vss_sc*)device_get_softc(dev);
	hv_vss_req_internal* reqp;

	while (!LIST_EMPTY(&sc->req_free_list)) {
		reqp = LIST_FIRST(&sc->req_free_list);
		LIST_REMOVE(reqp, link);
		free(reqp, M_DEVBUF);
	}

	while (!STAILQ_EMPTY(&sc->daemon_sc.to_notify_queue)) {
		reqp = STAILQ_FIRST(&sc->daemon_sc.to_notify_queue);
		STAILQ_REMOVE_HEAD(&sc->daemon_sc.to_notify_queue, slink);
		free(reqp, M_DEVBUF);
	}

	while (!STAILQ_EMPTY(&sc->daemon_sc.to_ack_queue)) {
		reqp = STAILQ_FIRST(&sc->daemon_sc.to_ack_queue);
		STAILQ_REMOVE_HEAD(&sc->daemon_sc.to_ack_queue, slink);
		free(reqp, M_DEVBUF);
	}

	while (!STAILQ_EMPTY(&sc->app_sc.to_notify_queue)) {
		reqp = STAILQ_FIRST(&sc->app_sc.to_notify_queue);
		STAILQ_REMOVE_HEAD(&sc->app_sc.to_notify_queue, slink);
		free(reqp, M_DEVBUF);
	}

	while (!STAILQ_EMPTY(&sc->app_sc.to_ack_queue)) {
		reqp = STAILQ_FIRST(&sc->app_sc.to_ack_queue);
		STAILQ_REMOVE_HEAD(&sc->app_sc.to_ack_queue, slink);
		free(reqp, M_DEVBUF);
	}
	return (0);
}