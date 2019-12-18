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
struct bfq_queue {int dummy; } ;
struct bfq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bfq_set_in_service_queue (struct bfq_data*,struct bfq_queue*) ; 
 struct bfq_queue* bfq_get_next_queue (struct bfq_data*) ; 

__attribute__((used)) static struct bfq_queue *bfq_set_in_service_queue(struct bfq_data *bfqd)
{
	struct bfq_queue *bfqq = bfq_get_next_queue(bfqd);

	__bfq_set_in_service_queue(bfqd, bfqq);
	return bfqq;
}