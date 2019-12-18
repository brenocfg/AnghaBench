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
struct ucma_abi_ud_param {int /*<<< orphan*/  qkey; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  ah_attr; scalar_t__ private_data_len; int /*<<< orphan*/  private_data; } ;
struct rdma_ud_param {int /*<<< orphan*/  qkey; int /*<<< orphan*/  qp_num; int /*<<< orphan*/  ah_attr; int /*<<< orphan*/ * private_data; scalar_t__ private_data_len; } ;
struct TYPE_4__ {struct rdma_ud_param ud; } ;
struct TYPE_3__ {TYPE_2__ param; } ;
struct cma_event {int /*<<< orphan*/  private_data; TYPE_1__ event; } ;

/* Variables and functions */
 int /*<<< orphan*/  ibv_copy_ah_attr_from_kern (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ucma_copy_ud_event(struct cma_event *event,
			       struct ucma_abi_ud_param *src)
{
	struct rdma_ud_param *dst = &event->event.param.ud;

	dst->private_data_len = src->private_data_len;
	if (src->private_data_len) {
		dst->private_data = &event->private_data;
		memcpy(&event->private_data, src->private_data,
		       src->private_data_len);
	}

	ibv_copy_ah_attr_from_kern(&dst->ah_attr, &src->ah_attr);
	dst->qp_num = src->qp_num;
	dst->qkey = src->qkey;
}