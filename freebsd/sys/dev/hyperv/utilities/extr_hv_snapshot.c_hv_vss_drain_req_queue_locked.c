#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct hv_vss_req_internal {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  to_ack_queue; int /*<<< orphan*/  to_notify_queue; } ;
struct TYPE_6__ {int /*<<< orphan*/  to_ack_queue; int /*<<< orphan*/  to_notify_queue; } ;
struct TYPE_7__ {TYPE_1__ app_sc; TYPE_2__ daemon_sc; } ;
typedef  TYPE_3__ hv_vss_sc ;

/* Variables and functions */
 int /*<<< orphan*/  SEARCH_REMOVE_REQ_LOCKED (struct hv_vss_req_internal*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hv_vss_req_internal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slink ; 

__attribute__((used)) static struct hv_vss_req_internal*
hv_vss_drain_req_queue_locked(hv_vss_sc *sc, uint64_t req_id)
{
	struct hv_vss_req_internal *reqp, *tmp;
	SEARCH_REMOVE_REQ_LOCKED(reqp, &sc->daemon_sc.to_notify_queue,
	    slink, tmp, req_id);
	if (reqp == NULL)
		SEARCH_REMOVE_REQ_LOCKED(reqp, &sc->daemon_sc.to_ack_queue,
		    slink, tmp, req_id);
	if (reqp == NULL)
		SEARCH_REMOVE_REQ_LOCKED(reqp, &sc->app_sc.to_notify_queue,
		    slink, tmp, req_id);
	if (reqp == NULL)
		SEARCH_REMOVE_REQ_LOCKED(reqp, &sc->app_sc.to_ack_queue, slink,
		    tmp, req_id);
	return (reqp);
}