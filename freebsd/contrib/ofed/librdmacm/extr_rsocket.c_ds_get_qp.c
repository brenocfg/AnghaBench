#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  union socket_addr {int dummy; } socket_addr ;
struct rsocket {struct ds_qp* qp_list; } ;
struct ds_qp {int /*<<< orphan*/  cm_id; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  ds_compare_addr (int /*<<< orphan*/ ,union socket_addr*) ; 
 int ds_create_qp (struct rsocket*,union socket_addr*,int /*<<< orphan*/ ,struct ds_qp**) ; 
 struct ds_qp* ds_next_qp (struct ds_qp*) ; 
 int /*<<< orphan*/  rdma_get_local_addr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ds_get_qp(struct rsocket *rs, union socket_addr *src_addr,
		     socklen_t addrlen, struct ds_qp **qp)
{
	if (rs->qp_list) {
		*qp = rs->qp_list;
		do {
			if (!ds_compare_addr(rdma_get_local_addr((*qp)->cm_id),
					     src_addr))
				return 0;

			*qp = ds_next_qp(*qp);
		} while (*qp != rs->qp_list);
	}

	return ds_create_qp(rs, src_addr, addrlen, qp);
}