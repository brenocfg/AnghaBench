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
struct TYPE_2__ {int (* event_handler ) (struct rdma_cm_id*,struct rdma_cm_event*) ;struct rdma_id_private* context; } ;
struct rdma_id_private {TYPE_1__ id; } ;
struct rdma_cm_id {int (* event_handler ) (struct rdma_cm_id*,struct rdma_cm_event*) ;struct rdma_id_private* context; } ;
struct rdma_cm_event {int dummy; } ;

/* Variables and functions */
 int stub1 (struct rdma_cm_id*,struct rdma_cm_event*) ; 

__attribute__((used)) static int cma_listen_handler(struct rdma_cm_id *id,
			      struct rdma_cm_event *event)
{
	struct rdma_id_private *id_priv = id->context;

	id->context = id_priv->id.context;
	id->event_handler = id_priv->id.event_handler;
	return id_priv->id.event_handler(id, event);
}