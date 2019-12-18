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
struct TYPE_2__ {int /*<<< orphan*/  discard_granularity; } ;
struct request_queue {TYPE_1__ limits; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  queue_var_show (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t queue_discard_granularity_show(struct request_queue *q, char *page)
{
	return queue_var_show(q->limits.discard_granularity, page);
}