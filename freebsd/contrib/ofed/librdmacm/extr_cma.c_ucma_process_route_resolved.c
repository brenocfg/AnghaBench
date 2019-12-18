#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  event; scalar_t__ status; } ;
struct cma_event {TYPE_3__ event; TYPE_4__* id_priv; } ;
struct TYPE_11__ {TYPE_2__* verbs; } ;
struct TYPE_10__ {TYPE_5__ id; } ;
struct TYPE_8__ {TYPE_1__* device; } ;
struct TYPE_7__ {scalar_t__ transport_type; } ;

/* Variables and functions */
 scalar_t__ IBV_TRANSPORT_IB ; 
 int /*<<< orphan*/  RDMA_CM_EVENT_ROUTE_ERROR ; 
 scalar_t__ af_ib_support ; 
 scalar_t__ ucma_query_path (TYPE_5__*) ; 
 scalar_t__ ucma_query_route (TYPE_5__*) ; 

__attribute__((used)) static void ucma_process_route_resolved(struct cma_event *evt)
{
	if (evt->id_priv->id.verbs->device->transport_type != IBV_TRANSPORT_IB)
		return;

	if (af_ib_support)
		evt->event.status = ucma_query_path(&evt->id_priv->id);
	else
		evt->event.status = ucma_query_route(&evt->id_priv->id);

	if (evt->event.status)
		evt->event.event = RDMA_CM_EVENT_ROUTE_ERROR;
}