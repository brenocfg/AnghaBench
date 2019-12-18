#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_3__ {struct ib_cm_id* ib; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct rdma_id_private {TYPE_1__ cm_id; TYPE_2__ id; } ;
struct ib_cm_id {int dummy; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ib_cm_id*) ; 
 int PTR_ERR (struct ib_cm_id*) ; 
 int /*<<< orphan*/  cma_req_handler ; 
 struct sockaddr* cma_src_addr (struct rdma_id_private*) ; 
 struct ib_cm_id* ib_cm_insert_listen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_get_service_id (TYPE_2__*,struct sockaddr*) ; 

__attribute__((used)) static int cma_ib_listen(struct rdma_id_private *id_priv)
{
	struct sockaddr *addr;
	struct ib_cm_id	*id;
	__be64 svc_id;

	addr = cma_src_addr(id_priv);
	svc_id = rdma_get_service_id(&id_priv->id, addr);
	id = ib_cm_insert_listen(id_priv->id.device, cma_req_handler, svc_id);
	if (IS_ERR(id))
		return PTR_ERR(id);
	id_priv->cm_id.ib = id;

	return 0;
}