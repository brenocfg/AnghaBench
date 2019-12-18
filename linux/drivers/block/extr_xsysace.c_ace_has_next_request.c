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
struct request_queue {struct ace_device* queuedata; } ;
struct ace_device {int /*<<< orphan*/  rq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ace_has_next_request(struct request_queue *q)
{
	struct ace_device *ace = q->queuedata;

	return !list_empty(&ace->rq_list);
}