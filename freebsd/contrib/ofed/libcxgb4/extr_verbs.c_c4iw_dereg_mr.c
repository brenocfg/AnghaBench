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
struct ibv_mr {int /*<<< orphan*/  lkey; TYPE_2__* pd; } ;
struct c4iw_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/ ** mmid2ptr; } ;
struct TYPE_4__ {TYPE_1__* context; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 size_t c4iw_mmid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int ibv_cmd_dereg_mr (struct ibv_mr*) ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 struct c4iw_dev* to_c4iw_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_c4iw_mr (struct ibv_mr*) ; 

int c4iw_dereg_mr(struct ibv_mr *mr)
{
	int ret;
	struct c4iw_dev *dev = to_c4iw_dev(mr->pd->context->device);

	ret = ibv_cmd_dereg_mr(mr);
	if (ret)
		return ret;

	pthread_spin_lock(&dev->lock);
	dev->mmid2ptr[c4iw_mmid(mr->lkey)] = NULL;
	pthread_spin_unlock(&dev->lock);

	free(to_c4iw_mr(mr));

	return 0;
}