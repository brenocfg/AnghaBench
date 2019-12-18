#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  dgid; } ;
struct TYPE_15__ {int /*<<< orphan*/  dlid; TYPE_5__ grh; } ;
struct TYPE_14__ {TYPE_7__ ah_attr; } ;
struct TYPE_16__ {TYPE_6__ ud; } ;
struct TYPE_9__ {TYPE_8__ param; } ;
struct cma_event {TYPE_4__* mc; TYPE_3__* id_priv; TYPE_1__ event; } ;
struct TYPE_12__ {int /*<<< orphan*/  mlid; int /*<<< orphan*/  mgid; } ;
struct TYPE_10__ {int /*<<< orphan*/  qp; } ;
struct TYPE_11__ {TYPE_2__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_attach_mcast (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rdma_seterrno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucma_process_join(struct cma_event *evt)
{
	evt->mc->mgid = evt->event.param.ud.ah_attr.grh.dgid;
	evt->mc->mlid = evt->event.param.ud.ah_attr.dlid;

	if (!evt->id_priv->id.qp)
		return 0;

	return rdma_seterrno(ibv_attach_mcast(evt->id_priv->id.qp,
					      &evt->mc->mgid, evt->mc->mlid));
}