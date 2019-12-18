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
struct vnet {int dummy; } ;
struct TYPE_4__ {struct vnet* net; } ;
struct TYPE_5__ {TYPE_1__ dev_addr; } ;
struct TYPE_6__ {TYPE_2__ addr; } ;
struct rdma_cm_id {int ps; int qp_type; TYPE_3__ route; int /*<<< orphan*/  event_handler; void* context; } ;
struct rdma_id_private {struct rdma_cm_id id; int /*<<< orphan*/  seq_num; int /*<<< orphan*/  mc_list; int /*<<< orphan*/  listen_list; int /*<<< orphan*/  handler_mutex; int /*<<< orphan*/  refcount; int /*<<< orphan*/  comp; int /*<<< orphan*/  qp_mutex; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  rdma_cm_event_handler ;
typedef  enum rdma_port_space { ____Placeholder_rdma_port_space } rdma_port_space ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct rdma_cm_id* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RDMA_CM_IDLE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  get_random_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct rdma_id_private* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

struct rdma_cm_id *rdma_create_id(struct vnet *net,
				  rdma_cm_event_handler event_handler,
				  void *context, enum rdma_port_space ps,
				  enum ib_qp_type qp_type)
{
	struct rdma_id_private *id_priv;

#ifdef VIMAGE
	if (net == NULL)
		return ERR_PTR(-EINVAL);
#endif
	id_priv = kzalloc(sizeof *id_priv, GFP_KERNEL);
	if (!id_priv)
		return ERR_PTR(-ENOMEM);

	id_priv->owner = task_pid_nr(current);
	id_priv->state = RDMA_CM_IDLE;
	id_priv->id.context = context;
	id_priv->id.event_handler = event_handler;
	id_priv->id.ps = ps;
	id_priv->id.qp_type = qp_type;
	spin_lock_init(&id_priv->lock);
	mutex_init(&id_priv->qp_mutex);
	init_completion(&id_priv->comp);
	atomic_set(&id_priv->refcount, 1);
	mutex_init(&id_priv->handler_mutex);
	INIT_LIST_HEAD(&id_priv->listen_list);
	INIT_LIST_HEAD(&id_priv->mc_list);
	get_random_bytes(&id_priv->seq_num, sizeof id_priv->seq_num);
	id_priv->id.route.addr.dev_addr.net = net;

	return &id_priv->id;
}