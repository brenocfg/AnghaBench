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
struct bfq_group {int /*<<< orphan*/  async_idle_bfqq; int /*<<< orphan*/ ** async_bfqq; } ;
struct bfq_data {int dummy; } ;

/* Variables and functions */
 int IOPRIO_BE_NR ; 
 int /*<<< orphan*/  __bfq_put_async_bfqq (struct bfq_data*,int /*<<< orphan*/ *) ; 

void bfq_put_async_queues(struct bfq_data *bfqd, struct bfq_group *bfqg)
{
	int i, j;

	for (i = 0; i < 2; i++)
		for (j = 0; j < IOPRIO_BE_NR; j++)
			__bfq_put_async_bfqq(bfqd, &bfqg->async_bfqq[i][j]);

	__bfq_put_async_bfqq(bfqd, &bfqg->async_idle_bfqq);
}