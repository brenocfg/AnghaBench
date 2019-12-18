#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bfq_queue {TYPE_1__* bfqd; } ;
struct bfq_group {int dummy; } ;
struct TYPE_2__ {struct bfq_group* root_group; } ;

/* Variables and functions */

struct bfq_group *bfq_bfqq_to_bfqg(struct bfq_queue *bfqq)
{
	return bfqq->bfqd->root_group;
}