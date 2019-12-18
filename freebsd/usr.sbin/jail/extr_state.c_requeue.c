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
struct cfjails {int dummy; } ;
struct cfjail {struct cfjails* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (struct cfjails*,struct cfjail*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct cfjails*,struct cfjail*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tq ; 

void
requeue(struct cfjail *j, struct cfjails *queue)
{
	if (j->queue != queue) {
		TAILQ_REMOVE(j->queue, j, tq);
		TAILQ_INSERT_TAIL(queue, j, tq);
		j->queue = queue;
	}
}