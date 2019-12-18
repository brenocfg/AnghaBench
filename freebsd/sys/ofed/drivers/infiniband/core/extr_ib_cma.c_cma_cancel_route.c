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
struct TYPE_2__ {int /*<<< orphan*/  port_num; int /*<<< orphan*/  device; } ;
struct rdma_id_private {scalar_t__ query; int /*<<< orphan*/  query_id; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_sa_cancel_query (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rdma_cap_ib_sa (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cma_cancel_route(struct rdma_id_private *id_priv)
{
	if (rdma_cap_ib_sa(id_priv->id.device, id_priv->id.port_num)) {
		if (id_priv->query)
			ib_sa_cancel_query(id_priv->query_id, id_priv->query);
	}
}