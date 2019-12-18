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
struct ibv_cq_1_0 {int /*<<< orphan*/  real_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibv_cq_1_0*) ; 
 int ibv_destroy_cq (int /*<<< orphan*/ ) ; 

int __ibv_destroy_cq_1_0(struct ibv_cq_1_0 *cq)
{
	int ret;

	ret = ibv_destroy_cq(cq->real_cq);
	if (ret)
		return ret;

	free(cq);
	return 0;
}