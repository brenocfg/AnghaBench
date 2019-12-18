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
struct pingpong_context {int /*<<< orphan*/  gidx; TYPE_1__* rem_dest; } ;
struct TYPE_4__ {int hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  dgid; } ;
struct ibv_ah_attr {int is_global; TYPE_2__ grh; } ;
struct TYPE_3__ {int /*<<< orphan*/  gid; } ;

/* Variables and functions */

__attribute__((used)) static void set_ah_attr(struct ibv_ah_attr *attr, struct pingpong_context *myctx,
			int index)
{
	attr->is_global = 1;
	attr->grh.hop_limit = 5;
	attr->grh.dgid = myctx->rem_dest[index].gid;
	attr->grh.sgid_index = myctx->gidx;
}