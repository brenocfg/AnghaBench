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
struct ibv_pd_1_0 {int /*<<< orphan*/  real_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ibv_pd_1_0*) ; 
 int ibv_dealloc_pd (int /*<<< orphan*/ ) ; 

int __ibv_dealloc_pd_1_0(struct ibv_pd_1_0 *pd)
{
	int ret;

	ret = ibv_dealloc_pd(pd->real_pd);
	if (ret)
		return ret;

	free(pd);
	return 0;
}