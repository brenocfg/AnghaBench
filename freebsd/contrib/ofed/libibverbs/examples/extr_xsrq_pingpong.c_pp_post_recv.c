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
struct ibv_sge {uintptr_t addr; int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; } ;
struct ibv_recv_wr {uintptr_t wr_id; int num_sge; struct ibv_sge* sg_list; int /*<<< orphan*/ * next; } ;
struct TYPE_4__ {int /*<<< orphan*/  srq; TYPE_1__* mr; int /*<<< orphan*/  size; scalar_t__ buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  lkey; } ;

/* Variables and functions */
 TYPE_2__ ctx ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ibv_post_srq_recv (int /*<<< orphan*/ ,struct ibv_recv_wr*,struct ibv_recv_wr**) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int pp_post_recv(int cnt)
{
	struct ibv_sge sge;
	struct ibv_recv_wr wr, *bad_wr;

	sge.addr = (uintptr_t) ctx.buf;
	sge.length = ctx.size;
	sge.lkey = ctx.mr->lkey;

	wr.next       = NULL;
	wr.wr_id      = (uintptr_t) &ctx;
	wr.sg_list    = &sge;
	wr.num_sge    = 1;

	while (cnt--) {
		if (ibv_post_srq_recv(ctx.srq, &wr, &bad_wr)) {
			fprintf(stderr, "Failed to post receive to SRQ\n");
			return 1;
		}
	}
	return 0;
}