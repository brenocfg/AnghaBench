#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int (* event_handler ) (TYPE_5__*,struct rdma_cm_event*) ;scalar_t__ qp_type; } ;
struct TYPE_13__ {struct ib_cm_id* ib; } ;
struct rdma_id_private {scalar_t__ state; TYPE_5__ id; int /*<<< orphan*/  handler_mutex; TYPE_4__ cm_id; int /*<<< orphan*/  refcount; } ;
struct TYPE_10__ {char* private_data; scalar_t__ private_data_len; } ;
struct TYPE_11__ {TYPE_1__ ud; } ;
struct rdma_cm_event {TYPE_2__ param; int /*<<< orphan*/  event; } ;
struct net_device {int dummy; } ;
struct ib_cm_id {int /*<<< orphan*/  cm_handler; struct rdma_id_private* context; } ;
struct TYPE_12__ {int /*<<< orphan*/  req_rcvd; } ;
struct ib_cm_event {scalar_t__ event; scalar_t__ private_data; TYPE_3__ param; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMA_CM_MRA_SETTING ; 
 int ECONNABORTED ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IB_CM_SIDR_REQ_PRIVATE_DATA_SIZE ; 
 scalar_t__ IB_CM_SIDR_REQ_RECEIVED ; 
 scalar_t__ IB_QPT_UD ; 
 scalar_t__ IS_ERR (struct rdma_id_private*) ; 
 int PTR_ERR (struct rdma_id_private*) ; 
 int /*<<< orphan*/  RDMA_CM_CONNECT ; 
 int /*<<< orphan*/  RDMA_CM_DESTROYING ; 
 int /*<<< orphan*/  RDMA_CM_EVENT_CONNECT_REQUEST ; 
 scalar_t__ RDMA_CM_LISTEN ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int cma_acquire_dev (struct rdma_id_private*,struct rdma_id_private*) ; 
 int /*<<< orphan*/  cma_check_req_qp_type (TYPE_5__*,struct ib_cm_event*) ; 
 scalar_t__ cma_comp (struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cma_deref_id (struct rdma_id_private*) ; 
 int /*<<< orphan*/  cma_exch (struct rdma_id_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cma_ib_handler ; 
 struct rdma_id_private* cma_id_from_event (struct ib_cm_id*,struct ib_cm_event*,struct net_device**) ; 
 struct rdma_id_private* cma_new_conn_id (TYPE_5__*,struct ib_cm_event*,struct net_device*) ; 
 struct rdma_id_private* cma_new_udp_id (TYPE_5__*,struct ib_cm_event*,struct net_device*) ; 
 int /*<<< orphan*/  cma_set_req_event_data (struct rdma_cm_event*,int /*<<< orphan*/ *,scalar_t__,int) ; 
 int cma_user_data_offset (struct rdma_id_private*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  ib_send_cm_mra (struct ib_cm_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  memset (struct rdma_cm_event*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_destroy_id (TYPE_5__*) ; 
 int stub1 (TYPE_5__*,struct rdma_cm_event*) ; 

__attribute__((used)) static int cma_req_handler(struct ib_cm_id *cm_id, struct ib_cm_event *ib_event)
{
	struct rdma_id_private *listen_id, *conn_id = NULL;
	struct rdma_cm_event event;
	struct net_device *net_dev;
	int offset, ret;

	listen_id = cma_id_from_event(cm_id, ib_event, &net_dev);
	if (IS_ERR(listen_id))
		return PTR_ERR(listen_id);

	if (!cma_check_req_qp_type(&listen_id->id, ib_event)) {
		ret = -EINVAL;
		goto net_dev_put;
	}

	mutex_lock(&listen_id->handler_mutex);
	if (listen_id->state != RDMA_CM_LISTEN) {
		ret = -ECONNABORTED;
		goto err1;
	}

	memset(&event, 0, sizeof event);
	offset = cma_user_data_offset(listen_id);
	event.event = RDMA_CM_EVENT_CONNECT_REQUEST;
	if (ib_event->event == IB_CM_SIDR_REQ_RECEIVED) {
		conn_id = cma_new_udp_id(&listen_id->id, ib_event, net_dev);
		event.param.ud.private_data = (char *)ib_event->private_data + offset;
		event.param.ud.private_data_len =
				IB_CM_SIDR_REQ_PRIVATE_DATA_SIZE - offset;
	} else {
		conn_id = cma_new_conn_id(&listen_id->id, ib_event, net_dev);
		cma_set_req_event_data(&event, &ib_event->param.req_rcvd,
				       ib_event->private_data, offset);
	}
	if (!conn_id) {
		ret = -ENOMEM;
		goto err1;
	}

	mutex_lock_nested(&conn_id->handler_mutex, SINGLE_DEPTH_NESTING);
	ret = cma_acquire_dev(conn_id, listen_id);
	if (ret)
		goto err2;

	conn_id->cm_id.ib = cm_id;
	cm_id->context = conn_id;
	cm_id->cm_handler = cma_ib_handler;

	/*
	 * Protect against the user destroying conn_id from another thread
	 * until we're done accessing it.
	 */
	atomic_inc(&conn_id->refcount);
	ret = conn_id->id.event_handler(&conn_id->id, &event);
	if (ret)
		goto err3;
	/*
	 * Acquire mutex to prevent user executing rdma_destroy_id()
	 * while we're accessing the cm_id.
	 */
	mutex_lock(&lock);
	if (cma_comp(conn_id, RDMA_CM_CONNECT) &&
	    (conn_id->id.qp_type != IB_QPT_UD))
		ib_send_cm_mra(cm_id, CMA_CM_MRA_SETTING, NULL, 0);
	mutex_unlock(&lock);
	mutex_unlock(&conn_id->handler_mutex);
	mutex_unlock(&listen_id->handler_mutex);
	cma_deref_id(conn_id);
	if (net_dev)
		dev_put(net_dev);
	return 0;

err3:
	cma_deref_id(conn_id);
	/* Destroy the CM ID by returning a non-zero value. */
	conn_id->cm_id.ib = NULL;
err2:
	cma_exch(conn_id, RDMA_CM_DESTROYING);
	mutex_unlock(&conn_id->handler_mutex);
err1:
	mutex_unlock(&listen_id->handler_mutex);
	if (conn_id)
		rdma_destroy_id(&conn_id->id);

net_dev_put:
	if (net_dev)
		dev_put(net_dev);

	return ret;
}