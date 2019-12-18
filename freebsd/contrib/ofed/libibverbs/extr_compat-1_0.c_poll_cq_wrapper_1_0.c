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
struct ibv_wc {int dummy; } ;
struct ibv_cq_1_0 {int /*<<< orphan*/  real_cq; TYPE_3__* context; } ;
struct TYPE_6__ {TYPE_2__* real_context; } ;
struct TYPE_4__ {int (* poll_cq ) (int /*<<< orphan*/ ,int,struct ibv_wc*) ;} ;
struct TYPE_5__ {TYPE_1__ ops; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,struct ibv_wc*) ; 

__attribute__((used)) static int poll_cq_wrapper_1_0(struct ibv_cq_1_0 *cq, int num_entries,
			       struct ibv_wc *wc)
{
	return cq->context->real_context->ops.poll_cq(cq->real_cq, num_entries, wc);
}