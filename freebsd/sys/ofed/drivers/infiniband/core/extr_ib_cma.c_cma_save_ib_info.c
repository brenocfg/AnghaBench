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
struct sockaddr_ib {int /*<<< orphan*/  sib_addr; int /*<<< orphan*/  sib_flowinfo; int /*<<< orphan*/  sib_pkey; void* sib_family; int /*<<< orphan*/  sib_sid_mask; scalar_t__ sib_scope_id; int /*<<< orphan*/  sib_sid; } ;
struct sockaddr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  src_addr; } ;
struct TYPE_4__ {TYPE_1__ addr; } ;
struct rdma_cm_id {TYPE_2__ route; } ;
struct ib_sa_path_rec {int /*<<< orphan*/  dgid; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  pkey; int /*<<< orphan*/  service_id; int /*<<< orphan*/  sgid; } ;

/* Variables and functions */
 void* AF_IB ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void cma_save_ib_info(struct sockaddr *src_addr,
			     struct sockaddr *dst_addr,
			     struct rdma_cm_id *listen_id,
			     struct ib_sa_path_rec *path)
{
	struct sockaddr_ib *listen_ib, *ib;

	listen_ib = (struct sockaddr_ib *) &listen_id->route.addr.src_addr;
	if (src_addr) {
		ib = (struct sockaddr_ib *)src_addr;
		ib->sib_family = AF_IB;
		if (path) {
			ib->sib_pkey = path->pkey;
			ib->sib_flowinfo = path->flow_label;
			memcpy(&ib->sib_addr, &path->sgid, 16);
			ib->sib_sid = path->service_id;
			ib->sib_scope_id = 0;
		} else {
			ib->sib_pkey = listen_ib->sib_pkey;
			ib->sib_flowinfo = listen_ib->sib_flowinfo;
			ib->sib_addr = listen_ib->sib_addr;
			ib->sib_sid = listen_ib->sib_sid;
			ib->sib_scope_id = listen_ib->sib_scope_id;
		}
		ib->sib_sid_mask = cpu_to_be64(0xffffffffffffffffULL);
	}
	if (dst_addr) {
		ib = (struct sockaddr_ib *)dst_addr;
		ib->sib_family = AF_IB;
		if (path) {
			ib->sib_pkey = path->pkey;
			ib->sib_flowinfo = path->flow_label;
			memcpy(&ib->sib_addr, &path->dgid, 16);
		}
	}
}